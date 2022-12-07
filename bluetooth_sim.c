#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN_FREQ 2400000000 //min frequency (hz) for bluetooth
#define MAX_FREQ 2483500000 //max frequency (hz) for bluetooth
#define KEY 10082001 //chosen key for encrypt/decrypt
#define KEY2 802001
#define KEY3 3
#define NUM_CHANNELS 40 //3 for inquiry 37 for use
#define CHANNEL_RANGE 2000000
#define CHANNEL_MAP_SEED 3

//a bluetooth device has a decrypted message, id, and mode
struct BluetoothDevice {
    char* decrypted_message;
    int id;
    int mode; // 0 for not connected, 1 for requested inquiry, 2 for connected
    int connected_id;
    int key;
    //int public_key;
    //int private_key;
};

int channel_map[NUM_CHANNELS-3]; //either 1 for used channel, or 0 for free channel
struct BluetoothDevice* inquiry_channel_map[3];

//method to initialize bluetooth device with message and channel map
void create_device(struct BluetoothDevice* device, char* in_message, int device_id) {
    device->decrypted_message = in_message;
    device->mode = 0; // device starts disconnected
    device->id = device_id;
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


//Search the inquiry channels for requests
//return 0 if device not found 1 if devicefound
int inquiry_search(struct BluetoothDevice* device)
{
	for(int i = 0; i < 3; i++ )
        {
                if(inquiry_channel_map[i] != NULL && inquiry_channel_map[i]->mode==1)
                {
                        connect(device, inquiry_channel_map[i]);
			return 1;
                }
        }
	return 0; // did not find device
}


void connect(struct BluetoothDevice* device1, struct BluetoothDevice* device2)
{
	
}


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
        str2[i] = message[i] + KEY3;
    }

    char* encrypted = str2;

    return encrypted;
}

//method to decrypt message
char* decrypt(char* message) {

    printf("%s\n", message);
    int length = (int) strlen(message);
    char str2[length];
    strcpy(str2, message);

    int i;
    for(i = 0; i < length; i++) {
        str2[i] = message[i] - KEY3;
    }

    char* decrypted = str2;

    return decrypted;
}

long generate_freq(int channel_num) {
    //choose frequency to transmit on based on range of frequencies in channel
    //all bluetooth frequencies between 2400 - 2483.5 MHZ, so 8.35E7 freqs in total
    //divided by 40 channels, each channel has 2,256,757 freqs to choose from
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


int main() {
	
	//int channel_map_seed = 3;
	//int channel_map[NUM_CHANNELS-3]; //either 1 for used channel, or 0 for free channel
	//struct BluetoothDevice* inquiry_channel_map[3] = {NULL, NULL, NULL};

	initialize_channel_map(CHANNEL_MAP_SEED);


}



