#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN_FREQ 2400000000 //min frequency (hz) for bluetooth
#define MAX_FREQ 2483500000 //max frequency (hz) for bluetooth
#define KEY 10082001 //chosen key for encrypt/decrypt
#define KEY2 802001
#define NUM_CHANNELS 37

//a bluetooth device has a decrypted message and a channel map to transmit to
struct BluetoothDevice {
    char* decrypted_message;
    int channel_map[NUM_CHANNELS]; //either 1 for used channel, or 0 for free channel
};

//a transmit package has an encrypted message and a frequency to transmit on
struct TransmitPackage {
    char* encrypted_message;
    long frequency;
};


//method to initialize bluetooth device with message and channel map
struct BluetoothDevice create_device(char in_message[], int channel_map_seed) {

    struct BluetoothDevice device;

    device.decrypted_message = in_message;

    for(int i = 0; i < NUM_CHANNELS; i++) {
        srand(channel_map_seed);   
        device.channel_map[i] = rand() % (1 - 0 + 1) + 1; //1 for used, 0 for not used
    }

    return device;
}


long generate_freq() {
    srand(time(0));
    long freq = rand() % (MAX_FREQ - MIN_FREQ + 1) + MIN_FREQ;
    return freq;
}

void frequency_hop(long original_freq) {
    //purpose: 

}

char* encrypt(char message[]) {

    int i;
    for(i = 0; i < strlen(message); i++) {
        message[i] = message[i] + (KEY/KEY2);
    }

    return message;
}

char* decrypt(char message[]) {

    int i;
    for(i = 0; i < strlen(message); i++) {
        message[i] = message[i] - KEY;
    }
    return message;
}

int main() {

    //initialize bluetooth devices
    struct BluetoothDevice device1 = create_device("hi I am device 1");

    /**/

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