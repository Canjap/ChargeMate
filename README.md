# ChargeMate

EID101-C Final Project: Serving up battery

## How It Works

This project involves the use of Raspberry Pis and Arduino modules to create a server-client system. The basic operation of the system is as follows: Raspberry Pi's, connected to buttons along a straight line, wait for a button press by a user. Upon registering a button press, the respective Pi sends the button's address (in this case, 1, 2, 3, etc.) to the server Raspberry Pi. The server Pi then forwards the button's address to an ESP32 module connected to an Arduino Uno R3 (which does not have WIFI capabilities). The ESP32 then forwards the button's address to the Arduino via UART implemented using `SoftwareSerial`. The Arduino Uno R3, which uses an Elegoo expansion board to drive servo motors, drives the button by matching it's address to a predetermined distance. Upon reaching the button, the Arduino robot car waits for 20 minutes, allowing users to connect to the attached battery pack and charge their devices before it moves onto to the next button. 

### Server Side

A Raspberry Pi 5 was tasked with server responsibilities, which was implemented using the `socket` Python library. The Pi connects to a home network, binds to a hostname and port number, and listens for connections. Multithreading is needed to handle multple clients, which was made using the `threading` Python library.

### Client Side

