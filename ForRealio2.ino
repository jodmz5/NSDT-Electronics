//Include libraries
#include "Arduino.h"
#include <SPI.h>
#include<RF24.h>

//Set up on SPI and signal pins  7 and 8
RF24 radio(7,8); //can change these two pins to any unused digital pins

// give the radios addresses
byte addresses[][6]={"1node","2node"};
int relaypin=4;
int temppin=A6;
int pressurepin=A2;
int lightpin=A1;
int tempval;
int pressureval;
int lightval; 
int tempthresh=100;// arbitrary thresholds
int pressurethresh=800000;
int lightthresh=2000000;


void setup() {
  Serial.begin(9600);
  Serial.println("Waiting for incoming data");
  radio.begin();//start the radio
  radio.setPALevel(RF24_PA_MIN);//sets power level to minimun. Must add capacitor to change to MAX. MAX will have longer range, but more current draw...
  radio.setDataRate(RF24_2MBPS);//quickest rate available
  radio.setChannel(1998);//Don't use something that will be a wifi name, ie MST
  radio.openWritingPipe(addresses[0]);// will SEND to the 2nd "addresses" index, 2node.
  radio.openReadingPipe(1,addresses[1]);//opens a reading pope 1 between the 2
  pinMode(relaypin,OUTPUT);
  pinMode(temppin, INPUT);

}

void loop() {
  delay(5);
  radio.stopListening();
  typedef struct{
  int temp=10;//analogRead(temppin);
  int pressure=190;//analogRead(strainpin);
  int light=167;//analogRead(lightpin);
  }
  A_t;
  A_t data;
  if(!radio.write(&data,sizeof(data))){}
  radio.startListening();
  typedef struct{
  int command;
  }
  B_t;
  B_t commands;
    if(radio.available()){
      while(radio.available()){
        radio.read(&commands, sizeof(commands));
      }
    }
    if(commands.command!=111){
      if(data.temp>=tempthresh||data.pressure>=pressurethresh||data.light>=lightthresh){
        digitalWrite(relaypin, HIGH);//or low, whichever side we use
      }
      else{
        Serial.println(commands.command);
      }
    }else{
      digitalWrite(relaypin, HIGH);
    }
    }
      

