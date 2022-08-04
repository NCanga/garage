/*
 * Project garageopener
 * Description:
 * Author:
 * Date:
 */
#include <particle-rf24.h>              //nrf24l01 library

SYSTEM_THREAD(ENABLED);
const pin_t MY_LED = D7;
RF24 radio(D0,D1);                      //Set the CE and CSE pins for SPI Connection
const byte address[6]= "00001";         //Set Channel Name
int subtime=millis();                   //Setup for variable to keep track of the last subscribe time
char text[32] = "";                        

void setup() {
    // Put initialization like pinMode and begin functions here.
    pinMode(D0,OUTPUT);                 // CE Output
    pinMode(D1,OUTPUT);                 //CSE Output
    
    SPI.begin();
    Serial.begin();
    radio.begin();
    radio.openReadingPipe(1, address);     //Set up the Channel
    radio.stopListening();              //Set as Transmitting
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    if(radio.available()){               // If there is activity on the channel
        radio.read(text, sizeof(text));   //Read the Messege
        if (millis()-subtime>10000){     //if the last publish time was x millis ago
            Serial.printf("recieved");
            Serial.printf(text);
            subtime=millis();        //Reset the delay
        }
    }
}