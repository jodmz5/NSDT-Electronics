#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_U.h>
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
void configureSensor(void)
{
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}
  
void setup() {
  Serial.begin(9600);
  tsl.begin();
  if(!tsl.begin()){
    Serial.print("Yeet chek your sensor");
    while(1)
    
}
configureSensor();
}

void loop() {
  sensor_event_t event;
  tsl.getEvent(&event);
  if(event.light){
    Serial.println(event.light);//in lux
  }
  else{
    Serial.println("Overload");
  }
delay(50);
}
