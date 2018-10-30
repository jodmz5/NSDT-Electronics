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
  Serial.print("Waiting for incoming data");
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(1998);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  radio.startListening();
  
}

void loop() {
  int command=Serial.read();
  if(radio.available()){
    while(radio.available()){
      radio.read(&data, sizeof(data));
    }
  }
  Serial.println(data.temp);
  Serial.println(data.strain);
  Serial.println(data.light);
  radio.stopListening();
  if(!radio.write(&command, sizeof(int)));
  radio.startListening();
}
