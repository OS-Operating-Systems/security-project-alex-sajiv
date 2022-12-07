#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN_FREQ 2400000000 //min frequency (hz) for bluetooth
#define MAX_FREQ 2483500000 //max frequency (hz) for bluetooth
#define KEY 10082001 //chosen key for encrypt/decrypt
#define KEY2 802001
#define KEY3 3
#define NUM_CHANNELS 37 //3 for inquiry 37 for use
#define CHANNEL_RANGE 2000000
#define CHANNEL_MAP_SEED 3

//a bluetooth device has a decrypted message, id, and mode
struct BluetoothDevice {
    char* decrypted_message;
    int id;
    int mode; // 0 for not connected, 1 for requested inquiry, 2 for connected
    int connected_id;
    int key;
    int channel;
    //int public_key;
    //int private_key;
};

int channel_map[NUM_CHANNELS]; //either 1 for used channel, or 0 for free channel
struct BluetoothDevice* inquiry_channel_map[3];

//method to initialize bluetooth device with message and channel map
void create_device(struct BluetoothDevice* device, char* in_message, int device_id) {
    device->decrypted_message = in_message;
    device->mode = 0; // device starts disconnected
    device->id = device_id;
    device->channel = 0;
}

//right now not being used might later
//Sets device message
void set_message(struct BluetoothDevice* device)
{
	//ask for message and get input. Set to a max size that can be sent in one packet
	device-> decrypted_message; 
}

//Initailizes 37 channels for channel map
void initialize_channel_map(int channel_map_seed)
{
	srand(channel_map_seed);
    	for(int i = 0; i < NUM_CHANNELS; i++)
	{
        	channel_map[i] = rand() % 2; //1 for used, 0 for not used
    	}
}

//Request inquiry in inquiry channels
void inquiry_request(struct BluetoothDevice* device)
{
	for(int i = 0; i < 3; i++ )
	{
		if(inquiry_channel_map[i] == NULL || inquiry_channel_map[i]->mode != 1)
		{
			inquiry_channel_map[i] = device;
			device->mode = 1;
			return;
		}
	}
	printf("Inquiry request error: all channels taken");
}

//Generate a key to be shared between device1 and device2
//This is called a symetric-key cipher where both devices use a single key real Bluetooth would use Advanced Encryption Standard (AES)
//Return the key
int generate_key()
{
        return 3;
}

int channel_hop(int beginning_channel)
{
    //channel hopping algorithm: iterate through channels by 5, if hits, get a frequency in range for that channel
    int hop = 5;
    int channel_count = beginning_channel + hop;
    int match = 0;
    while(match == 0) {
        if (channel_map[channel_count] == 0) { //if channel is free
            match = 1; //end loop
        }
        channel_count += hop; //hop up 5 channels (apparanently this is standard practice)
        if(channel_count >= NUM_CHANNELS) { //if go higher than 37
            channel_count -= NUM_CHANNELS; //reset to beginning
        }
    }
}

//Connect the two devices
//Give each device info on the device it is trying to connect with
void connect(struct BluetoothDevice* device1, struct BluetoothDevice* device2)
{
        device1 -> mode = 2;
        device2-> mode = 2;
        device1 -> connected_id = device2->id;
        device2 -> connected_id = device1->id;
        int generated_key = generate_key();
        device1 -> key = generated_key;
        device2 -> key = generated_key;
	int new_channel = channel_hop(device1->channel);
	device1->channel = new_channel;
	device2->channel = new_channel;
       		

}


//Search the inquiry channels for requests
//return 0 if device not found 1 if devicefound
int inquiry_search(struct BluetoothDevice* device)
{
	for(int i = 0; i < 3; i++ )
        {
                if(inquiry_channel_map[i] != NULL && inquiry_channel_map[i]->mode==1)
                {
                        connect(device,(struct BluetoothDevice*) inquiry_channel_map[i]);
			return 1;
                }
        }
	return 0; // did not find device
}


struct TransmitPacket {
    char* encrypted_message;
    long frequency;
    int sender_id;
};

//method to encrypt message
char* encrypt(char* message, int key) {

    int length = (int) strlen(message);
    char str2[length];
    strcpy(str2, message);

    int i;
    for(i = 0; i < length; i++) {
        str2[i] = message[i] + key;
    }

    char* encrypted = str2;

    return encrypted;
}

//method to decrypt message
char* decrypt(char* message, int key) {

    printf("%s\n", message);
    int length = (int) strlen(message);
    char str2[length];
    strcpy(str2, message);

    int i;
    for(i = 0; i < length; i++) {
        str2[i] = message[i] - key;
    }

    char* decrypted = str2;

    return decrypted;
}

long generate_freq(int channel_num) {
    //choose frequency to transmit on based on range of frequencies in channel
    //all bluetooth frequencies between 2400 - 2483.5 MHZ, so 8.35E7 freqs in total
    //each channel has 2,000,000 freqs to choose from and 2,500,000 left over
    //so the range for a channel is:
    //min = 2400 Mhz + (channel_num * 2,000,000)
    //max = min + (channel_num + 1) * 2,000,000
    //each channel is 2MHz wide
    long channel_min = MIN_FREQ + (channel_num * CHANNEL_RANGE);
    long channel_max = channel_min + CHANNEL_RANGE;

    srand(time(0));

    long freq = rand() % (channel_max - channel_min + 1) + channel_min;

    //for random frequency in entire range
    //long freq = rand() % (MAX_FREQ - MIN_FREQ + 1) + MIN_FREQ;
    return freq;
}



//method to initialize packet
void create_packet(struct TransmitPacket* packet, struct BluetoothDevice* device) {

    //encrypt device's message and store in packet to send
    packet->encrypted_message = encrypt(device->decrypted_message, device->key);

    //choose a channel to transmit on based on channel selection algorithm
    //(if device.channel_map[i] is 0, its a free channel, and we can use it)

    int channel_count = channel_hop(device->channel);
    //now channel count should have a free channel
    //below utilizes frequency hop algorithm
    packet->frequency = generate_freq(channel_count);

    packet->sender_id = device->id;
}



int allow_connection(struct BluetoothDevice* device, long freq) {
    //allow connection if channels match
   
   //Determine what channel this freq would be on	
   long freq_channel = freq - MIN_FREQ; //MIN freq is 2,400,000,000
   freq_channel = freq_channel/CHANNEL_RANGE;

   if(device->channel == freq_channel && device->mode == 2) {
        printf("Successful connection\n");
        return 1;
    }
    else {
        printf("Could not connect\n");
        return 2;
    }
}

int authenticate(int sender_id, int expected_id)
{
	if(sender_id == expected_id)
	{
		printf("Correct Sender ID\n");
		return 1;
	}
	else
	{
		printf("Incorrect Sender ID\n");
		return 0;
	}
}

void recieve_packet(struct TransmitPacket* incoming_packet, struct BluetoothDevice* receiving_device)
{
	
}



int main() {
	
	//Initialize channel map and devices to be used
	initialize_channel_map(CHANNEL_MAP_SEED);
	struct BluetoothDevice* device1  = (struct BluetoothDevice*) malloc(sizeof(struct BluetoothDevice));
	struct BluetoothDevice* device2  = (struct BluetoothDevice*) malloc(sizeof(struct BluetoothDevice));
	char* message1 = "hi";
	char* message2 = "hello";
	
	create_device(device1, message1, 1);
	create_device(device2, message2, 2);	
	
	printf("device1 message: %s\n", device1->decrypted_message);
	printf("Device 1 mode before inquiry: %d\n", device1->mode);
	printf("device2 before connection: %s\n", device2->decrypted_message);
	
	
	//Inquiry	
	inquiry_request(device1);
	printf("Device 1 mode after inquiry: %d\n", device1->mode);

	if(inquiry_search(device2) == 0)
	{
		printf("No device is available to connect to");
	}
		
	printf("Device 1 connected to device id: %d\n", device1->connected_id);
	
	//Send message
	
	//create packet for device 1 with encrypted message
	struct TransmitPacket* send_packet = (struct TransmitPacket*) malloc(sizeof(struct TransmitPacket));
	create_packet(send_packet, device1);
	printf("Packet encrypted message: %s\n", send_packet->encrypted_message);
	printf("Device 1 channel: %d\nPacket frequency: %ld\n", device1->channel, send_packet->frequency);
	allow_connection(device2, send_packet->frequency);
	



}



