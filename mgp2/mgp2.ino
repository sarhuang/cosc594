#include <CapacitiveSensor.h>
CapacitiveSensor   cs_12_2 = CapacitiveSensor(12,2);    //blue
CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);    //black    
CapacitiveSensor   cs_12_4 = CapacitiveSensor(12,4);    //gray     
CapacitiveSensor   cs_12_5 = CapacitiveSensor(12,5);    //brown
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);    //white 
CapacitiveSensor   cs_12_7 = CapacitiveSensor(12,7);    //green  
CapacitiveSensor   cs_12_8 = CapacitiveSensor(12,8);    //purple     
CapacitiveSensor   cs_12_9 = CapacitiveSensor(12,9);    //orange
CapacitiveSensor   cs_12_10 = CapacitiveSensor(12,10);  //yellow     
CapacitiveSensor   cs_12_11 = CapacitiveSensor(12,11);  //blue

int treshold = 500;
int digPin = 13;

void setup()                    
{
  cs_12_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  pinMode(digPin, OUTPUT);
}

void loop()                    
{
  long Sensor2 =  cs_12_2.capacitiveSensor(30);
  long Sensor3 =  cs_12_3.capacitiveSensor(30);
  long Sensor4 =  cs_12_4.capacitiveSensor(30);
  long Sensor5 =  cs_12_5.capacitiveSensor(30);
  long Sensor6 =  cs_12_6.capacitiveSensor(30);
  long Sensor7 =  cs_12_7.capacitiveSensor(30);
  long Sensor8 =  cs_12_8.capacitiveSensor(30);
  long Sensor9 =  cs_12_9.capacitiveSensor(30);
  long Sensor10 =  cs_12_10.capacitiveSensor(30);
  long Sensor11 =  cs_12_11.capacitiveSensor(30);
        

  Serial.print(Sensor2);             
  Serial.print(" ");       

  Serial.print(Sensor3);                
  Serial.print(" ");       

  Serial.print(Sensor4);               
  Serial.print(" ");     

  Serial.print(Sensor5);                 
  Serial.print(" ");   

  Serial.print(Sensor6);                 
  Serial.print(" ");   

  Serial.print(Sensor7);                 
  Serial.print(" ");

  Serial.print(Sensor8);                  
  Serial.print(" ");  

  Serial.print(Sensor9);                  
  Serial.print(" ");  

  Serial.print(Sensor10);                  
  Serial.print(" ");  

  Serial.println(Sensor11);                               




  if (Sensor2 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 131);
    //Serial.print("A\n");
  } 
  if (Sensor3 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 165);
    //Serial.print("C\n");
  } 
  if (Sensor4 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 175);
    //Serial.print("D\n");
  } 
  if (Sensor5 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 196);
    //Serial.print("E\n");
  } 
  if (Sensor6 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 220);
    //Serial.print("F\n");
  } 
  if (Sensor7 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 247);
    //Serial.print("G\n");
  } 
  if (Sensor8 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 262);
    //Serial.print("H\n");
  } 
 if (Sensor9 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 147);   
    //Serial.print("B\n");
  } 
  if (Sensor10 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 147);   
    //Serial.print("B\n");
  } 
  if (Sensor11 > treshold){
    digitalWrite(digPin, HIGH);
    //tone(speaker, 147);   
    //Serial.print("B\n");
  } 
  
  if (Sensor2<=treshold & Sensor3<=treshold & Sensor4<=treshold & Sensor5<=treshold & Sensor6<=treshold & Sensor7<=treshold & Sensor8<=treshold & Sensor9<=treshold
  & Sensor10<=treshold & Sensor11<=treshold){
    //noTone(speaker);
    digitalWrite(digPin, LOW);
  }
}
