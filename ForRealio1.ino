#include "Arduino.h"
#include<SPI.h>
#include<RF24.h>
RF24 radio(7,8);
byte addresses[][6]={"1node","2node"};
typedef struct{
  int temp;
  int strain;
  int light;
}
A_t;
A_t data;

void setup() {
  Serial.begin(9600);
 // Serial.println("Waiting for incoming data");
 // Serial.println("Temperature: \t Strain: \t Light:");
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(1998);
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening();
  
}

void loop() {
 
  typedef struct{
    int command;
  }
  B_t;
  B_t commands;
  if(Serial.available()>0){
    commands.command=Serial.read();
  }
  if(radio.available()){
    while(radio.available()){
      radio.read(&data, sizeof(data));
    }
  }
  
  Serial.print(data.temp);
  Serial.print("\t\t");
  Serial.print(data.strain);
  Serial.print("\t\t");
  Serial.print(data.light);
  Serial.print("\t\t");
  Serial.print(commands.command);
  Serial.println("\t\t");
  delay(5);
  radio.stopListening();
 if(! radio.write(&commands, sizeof(commands))){
  
 }
  delay(5);
  radio.startListening();
}
