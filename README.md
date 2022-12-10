# security-project-alex-sajiv
# What?
This is program to simulate a bluetooth pairing, and send 1 packet of encrypted data to a paired device.  

# Why Is This Important?
Radio communication security is important because almost all devices today transmit and/or recieve radio frequencies. So, there's radio waves constantly all around us in our daily lives. A lot of these radio frequencies are unencrypted and unprotected from anybody to intercept. This is a problem since it is unwanted for many  radio communications to have unauthorized people such as eavesdroppers and hackers understand what is being sent. Examples of radio signals that could be easily intercepted include airport communications, device broadcasts, weather stations, satellites, and emergency communications. Although there are many unprotected radio frequencies there are some that are protected. These would include things such as Bluetooth and Wi-Fi. These radio communications, although protected, are still at risk of eavesdroppers and hackers that have descovered how to decrypt these radio signals. So, it is important to continuously aim to improve radio signal security methods and encryptions.



# Description of Each Person's Role in Our Program
Alex:  
- Inquiry/channel maps  
- Inquiry request/search  
- Connect  
- Allow connection and authentication  
- Receive packet  
- Debugging  


Sajiv:  
- Channel hop algorithm  
- Generate frequency within channel  
- Encrytion and decryption  
- Transmit packet struct and create packet
- Bluetooth Device struct  
- Debugging  


# Code Used to Compile Final Program

`gcc bluetooth_sim.c`

# Code to Run Final Program

`./a.out`


# Description of How Program Works

## Device Creation
Our program starts by creating 2 bluetooth devices. Our bluetooth devices have a message, stored in a decrypted state, a mode (// 0 for not connected, 1 for requested inquiry, 2 for connected), an ID, another ID for the device it is connected to, a key for encryption, and a channel. They both are initialized in mode 0, disconnected mode. The channel for the device is assigned to 0. The device ID and message to be stored are passed into our `create_device(struct BluetoothDevice* device, char in_message[], int device_id)` method. Device 1 starts with the "i love coding" message and id 1, while device 2 starts with a blank message and id 2. 

## Pairing/Inquiry phase
We then start the inquiry, or pairing process. We call `void inquiry_request(struct BluetoothDevice* device)` on device 1, which puts it in pairing mode after checking our `inquiry_channel_map`. This is an array of all devices currently in pairing mode. As long as that array isn't full, `void inquiry_request(struct BluetoothDevice* device)` adds the passed device to `inquiry_channel_map` and changes its mode to 1, for pairing mode. We allowed a total of 3 devices that could simultaneously be in pairing mode in our program.

We then call `inquiry_search(struct BluetoothDevice* device)` on device2, where it searches the `inquiry_channel_map` to see if a device is available to pair to. If it returns 1, pair using `void connect(struct BluetoothDevice* device1, struct BluetoothDevice* device2)`. Both devices get put in mode 2, for connected, and their connected ids get updated to the other device's id. We generate a key for both devices to use for later encryption and decryption using `generate_key()`. Both channels are given a channel based on the `int channel_hop(int beginning_channel)`. This method uses a channel hopping algorithm to pick a random channel to communicate on. This algorithm is a simplified version of the real version from Bluetooth.

## Communication phase




# Extra
The files aes.c and aes.h include an example of an AES encryption that would typially be used in Bluetooth encryption. Although it was not implemented in the program, we thought it would be cool to still include these files. The URL of the source for these files are included at the top of these files.



# What We Would Improve
- Incorporating hardware  -> Include an antenna receive the radio signals and a device to transmit radio signals. This would allow the program to use real radio communications instead of it being simulated   
- Better encryption -> This could be done by figuring out how to implement the AES encryption and decryption into the project   
- More devices -> Simulate the connection between more than just two devices   
- Transmit other types of data -> Instead of transmitting and receiving text data we could also transmit and receive other sorts of data such as sound   



# Honor Code Statement

The honor code was not violated during this assignment


