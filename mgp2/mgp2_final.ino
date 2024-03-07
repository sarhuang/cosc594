/*Sarah Huang, Christian Tongate
March 6th, 2024

Code for Cheerio Slider, an alternative numerical input device. This code primarily makes
use of the Capacitive Sensor library to detect the presence of a cheerio on a copper tape
pad. If the pad corresponding to a given number on the range of 0-8 reads as high then that
number is printed out.
*/

#include <CapacitiveSensor.h>

//Initialize capacitive sensors, comments correspond pins to wire colors
CapacitiveSensor   cs_12_2 = CapacitiveSensor(11,2);    //blue
CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);    //black    
CapacitiveSensor   cs_12_4 = CapacitiveSensor(13,4);    //gray     
CapacitiveSensor   cs_12_5 = CapacitiveSensor(14,5);    //brown
CapacitiveSensor   cs_12_6 = CapacitiveSensor(15,6);    //white 
CapacitiveSensor   cs_12_7 = CapacitiveSensor(16,7);    //green  
CapacitiveSensor   cs_12_8 = CapacitiveSensor(17,8);    //purple     
CapacitiveSensor   cs_12_9 = CapacitiveSensor(18,9);    //orange

int threshold = 100;
//char num_input = 'A'; 
int counter = 0;
int dialPin = 20;
int dialVal = 0;

void setup(){
  cs_12_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  counter = 0;
}

void loop(){
  //Get readings on capactiive sensor
  long Sensor2 =  cs_12_2.capacitiveSensor(30);
  long Sensor3 =  cs_12_3.capacitiveSensor(30);
  long Sensor4 =  cs_12_4.capacitiveSensor(30);
  long Sensor5 =  cs_12_5.capacitiveSensor(30);
  long Sensor6 =  cs_12_6.capacitiveSensor(30);
  long Sensor7 =  cs_12_7.capacitiveSensor(30);
  long Sensor8 =  cs_12_8.capacitiveSensor(30);
  long Sensor9 =  cs_12_9.capacitiveSensor(30);

  //Used for debugging, toggles whether or not "Number input: x" lines are displayed
  dialVal = analogRead(dialPin);

  //Determine which number is currently being input on cheerio slider
  if(Sensor2 < 100 && Sensor3 < 100 && Sensor4 < 100 && Sensor5 < 100 && Sensor6 < 100 && Sensor7 < 100 && Sensor8 < 100 && Sensor9 < 100){
    num_input = '0';
  }
  else if(Sensor2 > 100){
    num_input = '1';
  }
  else if(Sensor3 > 100){
    num_input = '2';
  }
  else if(Sensor4 > 100){
    num_input = '3';
  }
  else if(Sensor5 > 100){
    num_input = '4';
  }
  else if(Sensor6 > 100){
    num_input = '5';
  }
  else if(Sensor7 > 100){
    num_input = '6';
  }
  else if(Sensor8 > 100){
    num_input = '7';
  }
  else if(Sensor9 > 100){
    num_input = '8';
  }
  
  //Prints seriall monitor line
  if(dialVal == 0){
    Serial.print("Number input: ");
    Serial.print(num_input);
    Serial.println();
    delay(100);
  }

}
