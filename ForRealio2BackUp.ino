//Include libraries
#include "Arduino.h"
#include <SPI.h>
#include<RF24.h>

//Set up on SPI and signal pins  7 and 8
RF24 radio(7,8); //can change these two pins to any unused digital pins

// give the radios addresses
byte addresses[][6]={"1node","2node"};
int relaypin=4;
int temppin=A5;
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
  digitalWrite(relaypin, HIGH); // might be low depending on how relays work

}

void loop() {
  delay(5);
  radio.stopListening();
  typedef struct{
  int temp=analogRead(temppin);
  int pressure=190;//analogRead(strainpin);
  int light=167;//analogRead(lightpin);
  }
  A_t;
  A_t data;
  Serial.print(data.temp);
  for(int i=0; i<=(10^6); i++){
   if(data.temp>=tempthresh){
    digitalWrite(relaypin, HIGH);//might be HIGH based on how relays work
   }
  }
 /* }else if(data.strain>=strainthresh){
    digitalWrite(relaypin, HIGH);
  }else if(data.light>=lightthresh){
    digitalWrite(relaypin, HIGH);
  }*/
  if(!radio.write(&data, sizeof(data))){
  }
  radio.startListening();
  if(radio.available()){
    
    while(radio.available()){
      typedef struct{
        int command;
      }
      B_t;
      B_t commands;
      radio.read(&commands, sizeof(commands));
      Serial.println(commands.command);
      if(commands.command==120){
        digitalWrite(relaypin,HIGH);}
      else if(commands.command==111){
        digitalWrite(relaypin,LOW);}
      else{
        digitalWrite(relaypin,LOW);
      }
      }
      }
        return;
    }
  
 
  
  

  
    

  
  
   
     
    


 


