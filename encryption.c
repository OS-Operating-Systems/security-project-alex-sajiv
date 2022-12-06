#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN_FREQ 2400000000 //min frequency (hz) for bluetooth
#define MAX_FREQ 2483500000 //max frequency (hz) for bluetooth
#define KEY 10082001 //chosen key for encrypt/decrypt
#define KEY2 802001
#define NUM_CHANNELS 37
#define CHANNEL_RANGE 2256757

//a bluetooth device has a decrypted message and a channel map to transmit to
struct BluetoothDevice {
    char* decrypted_message;
    int channel_map[NUM_CHANNELS]; //either 1 for used channel, or 0 for free channel
};



//method to initialize bluetooth device with message and channel map
struct BluetoothDevice create_device(char in_message[], int channel_map_seed) {

    struct BluetoothDevice device;

    device.decrypted_message = in_message;

    srand(channel_map_seed);
    for(int i = 0; i < NUM_CHANNELS; i++) {
        device.channel_map[i] = rand() % 2; //1 for used, 0 for not used
    }

    return device;
}

//a transmit packet has an encrypted message and a frequency to transmit on
struct TransmitPacket {
    char* encrypted_message;
    long frequency;
};

//method to encrypt message
char* encrypt(char* message) {

    int length = (int) strlen(message);
    char str2[length];
    strcpy(str2, message);

    int i;
    for(i = 0; i < length; i++) {
        str2[i] = message[i] + (KEY/KEY2);
    }

    char* encrypted = str2;

    return encrypted;
}

//method to decrypt message
char* decrypt(char* message) {

    int length = (int) strlen(message);
    char str2[length];
    strcpy(str2, message);

    int i;
    for(i = 0; i < length; i++) {
        str2[i] = message[i] - (KEY/KEY2);
    }

    char* decrypted = str2;

    return decrypted;
}

//calculate frequency for channel
//this is the frequency hopping algorithm
long generate_freq(int channel_num) {
    //choose frequency to transmit on based on range of frequencies in channel
    //all bluetooth frequencies between 2400 - 2483.5 MHZ, so 8.35E7 freqs in total
    //divided by 37 channels, each channel has 2,256,757 freqs to choose from
    //so the range for a channel is:
    //min = 2400 Mhz + (channel_num * 2,256,757)
    //max = min + (channel_num + 1) * 2,256,757

    long channel_min = MIN_FREQ + (channel_num * CHANNEL_RANGE);
    long channel_max = channel_min + CHANNEL_RANGE;

    srand(time(0));

    long freq = rand() % (channel_max - channel_min + 1) + channel_min;

    //for random frequency in entire range
    //long freq = rand() % (MAX_FREQ - MIN_FREQ + 1) + MIN_FREQ;
    return freq;
}
//method to initialize transmit packet
struct TransmitPacket create_packet(struct BluetoothDevice device) {
    
    struct TransmitPacket packet;

    //encrypt device's message and store in packet to send
    packet.encrypted_message = encrypt(device.decrypted_message);

    //choose a channel to transmit on based on channel selection algorithm
    //(if device.channel_map[i] is 0, its a free channel, and we can use it)

    //channel hopping algorithm: iterate through channels by 5, if hits, get a frequency in range for that channel
    int channel_count = 0;
    int match = 0;
    int hop = 5;
    int channel_num = 0;
    while(match == 0) {
        if (device.channel_map[channel_count] == 0) { //if channel is free
            match = 1; //end loop
        }
        channel_count += hop; //hop up 5 channels (apparanently this is standard practice)
        if(channel_count >= NUM_CHANNELS) { //if go higher than 37
            channel_count -= NUM_CHANNELS; //reset to beginning
        }
    }
    //now channel count should have a free channel
    //below utilizes frequency hop algorithm
    packet.frequency = generate_freq(channel_count);
    return packet;
}

int allow_connection(long freq1, long freq2) {
    //allow connection if frequencies match
    if(freq1 == freq2) {
        printf("Successful connection\n");
        return 1;
    }
    else {
        printf("Could not connect\n");
        return 0;
    }
}

//method to update device with packet if successful connection
//return 1 if successful update
//return 0 if unc
int receive_packet(struct TransmitPacket incoming_packet, struct BluetoothDevice* receiving_device) {

    printf("%s\n", decrypt(incoming_packet.encrypted_message));
    //get receiving frequency from receiving device
    long receiving_frequency = create_packet(*receiving_device).frequency;

    //if frequency matches incoming packet's frequency, attempt to decrypt
    int connection_success = allow_connection(incoming_packet.frequency, receiving_frequency);
    if(connection_success == 1) {
        receiving_device->decrypted_message = decrypt(incoming_packet.encrypted_message);
        return 1;
    }
    else {
        printf("Could not update device\n");
        return 0;
    }
    
}




int main() {

    //initialize bluetooth devices with same seed so they have matching channel maps
    int seed = 3;
    struct BluetoothDevice device1 = create_device("hi I am device 1", seed);
    struct BluetoothDevice device2 = create_device("hi I am device 2", seed);

    printf("device1 message: %s\n", device1.decrypted_message);
    printf("device2 before connection: %s\n", device2.decrypted_message);


    //create packet for device 1 with encryped message
    struct TransmitPacket send_packet = create_packet(device1);
    //printf("%s\n", send_packet.encrypted_message);

    //attempt to transmit to device 2
    int success_transmit = receive_packet(send_packet, &device2);

    //show device1's message on device2
    printf("device2 after connection: %s\n", device2.decrypted_message);

    //need to implement some kind of send/receive functionality, right now only sends
    //so technically, device2 needs a receive packet that will decode encrypted packet
    //make receive packet if device2 has good frequency


    /*

    //testing channels
    /*
    for (int i = 0; i < NUM_CHANNELS; i++) {

        printf("%d, ", device1.channel_map[i]);
    }
    printf("\n");

    //create packet for device 2
    printf("%s\n", send_packet.encrypted_message);
    printf("device1 packet frequency %ld\n", send_packet.frequency);

    struct TransmitPacket receive_packet = create_packet(device2);
    printf("%s\n", receive_packet.encrypted_message);
    printf("device2 packet frequency %ld\n", receive_packet.frequency);

    int connection_success = allow_connection(send_packet.frequency, receive_packet.frequency);
    long freq = generate_freq();
    printf("%ld\n", freq);

    char message[] = "hi";
    char* encrypted_message = encrypt(message);
    printf("%s\n", encrypted_message);

    char* decrypted_message = decrypt(encrypted_message);
    printf("%s\n", decrypted_message);

    */
    return 0;
}