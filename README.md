# security-project-alex-sajiv
# What?
This is program to simulate a bluetooth pairing, and send 1 packet of encrypted data to a paired device.  

# Why Is This Important?
Radio communication security is important because almost all devices today transmit and/or recieve radio frequencies. So, there's radio waves constantly all around us in our daily lives. Alot of these radio frequencies are unencrypted and unprotected from anybody to intercept. This is a problem since it is unwanted for many  radio communications to have unauthorized people such as eavesdroppers and hackers understand what is being sent. Examples of radio signals that could be easily intercepted include airport communications, device broadcasts, weather stations, satellites, and emergency communications. Although there are many unprotected radio frequencies there are some that are. These would include things such as Bluetooth and Wi-Fi. These radio communications, although protected, are still at risk of eavesdroppers and hackers that have descovered how to decrypt these radio signals. So, it is important to continuously aim to improve radio signal security methods and encryptions.



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
- Debugging  


# Code Used to Compile Final Program

gcc bluetooth_sim.c

# Code to Run Final Program

./a.out


#Description of How Program Works




# Extra
The files aes.c and aes.h include an example of an AES encryption that would typially be used in Bluetooth encryption. Although it was not implemented in the program, we thought it would be cool to still include these files. The URL of the source for these files are included at the top of these files.



# What We Would Improve
- Incorporating hardware  -> Include an antenna receive the radio signals and a device to transmit radio signals. This would allow the program to use real radio communications instead of it being simulated   
- Better encryption -> This could be done by figuring out how to implement the AES encryption and decryption into the project   
- More devices -> Simulate the connection between more than just two devices   
- Transmit other types of data -> Instead of transmitting and receiving text data we could also transmit and receive other sorts of data such as sound   



# Honor Code Statement

The honor code was not violated during this assignment


