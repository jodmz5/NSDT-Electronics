//Include libraries
#include "Arduino.h"
#include <SPI.h>
#include<RF24.h>
//uint32_t test[]={6,7,8,9};

//Set up on SPI and signal pins  7 and 8
RF24 radio(7,8); //can change these two pins to any unused digital pins

// give the radios addresses
byte addresses[][6]={"1node","2node"};
int relaypin=4;
int temppin=A1;
int strainpin=A2;
int lightpin=A5;
int tempval;
int strainval;
int lightval;
int tempthresh=100;// arbitrary thresholds
int strainthresh=8;
int lightthresh=200;
int command;



void setup() {
  Serial.begin(9600);
  Serial.println("Waiting for incoming data");
  radio.begin();//start the radio
  radio.setPALevel(RF24_PA_MIN);//sets power level to minimun. Must add capacitor to change to MAX. MAX will have longer range, but more current draw...
  radio.setDataRate(RF24_2MBPS);//quickest rate available
  radio.setChannel(1998);//Don't use something that will be a wifi name, ie MST
  radio.openWritingPipe(addresses[1]);// will SEND to the 2nd "addresses" index, 2node.
  radio.openReadingPipe(1,addresses[0]);//opens a reading pope 1 between the 2
  radio.stopListening();
  digitalWrite(relaypin, HIGH); // might be low depending on how relays work

}

void loop() {
  typedef struct{
  int temp=249;//analogRead(temppin);
  int strain=2;//analogRead(strainpin);
  int light==45//analogRead(lightpin);
  }
  A_t;
  A_t data;
  if(data.temp>=tempthresh){
    digitalWrite(relaypin, LOW);//might be HIGH based on how relays work
  }else if(data.strain>=strainthresh){
    digitalWrite(relaypin, LOW);
  }else if(data.light>=lightthresh){
    digitalWrite(relaypin, LOW);
  }
  if(!radio.write(&data, sizeof(data))){
    Serial.println("NOT SENT");
  }
  
  if(radio.available()){
    radio.startListening();
    while(radio.available()){
      radio.read(&command, sizeof(int));
      Serial.println(command);
      if(command==120){
        digitalWrite(relaypin,LOW);
      }else if(command==111){
        digitalWrite(relaypin, HIGH);
      }
      
    }
  }
  radio.stopListening();

  }


