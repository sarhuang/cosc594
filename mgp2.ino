#include <CapacitiveSensor.h>
#include <Keyboard.h>

CapacitiveSensor   cs_12_2 = CapacitiveSensor(12,2);    //blue
CapacitiveSensor   cs_12_3 = CapacitiveSensor(12,3);    //black    
CapacitiveSensor   cs_12_4 = CapacitiveSensor(12,4);    //gray     
CapacitiveSensor   cs_12_5 = CapacitiveSensor(12,5);    //brown
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);    //white 
CapacitiveSensor   cs_12_7 = CapacitiveSensor(12,7);    //green  
CapacitiveSensor   cs_12_8 = CapacitiveSensor(12,8);    //purple     
CapacitiveSensor   cs_12_9 = CapacitiveSensor(12,9);    //orange
//CapacitiveSensor   cs_12_10 = CapacitiveSensor(12,10);  //yellow     
CapacitiveSensor   cs_12_11 = CapacitiveSensor(12,11);  //blue

int threshold[8] = {};
int digPin = 14;
char num_input = 'A';
int counter = 0;
long sensor2_vals[30];
long sensor3_vals[30];
long sensor4_vals[30];
long sensor5_vals[30];
long sensor6_vals[30];
long sensor7_vals[30];
long sensor8_vals[30];
long sensor9_vals[30];


void setup(){
  cs_12_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  pinMode(digPin, OUTPUT);
  Keyboard.begin(); 
  counter = 0;
}


long average(long *array, int len){
  long sum = 0;
  for(int i = 0; i < len; i++){
    sum += array[i];
  }
  sum /= len;
  return sum;
}



void loop(){
  long Sensor2 =  cs_12_2.capacitiveSensor(30);
  long Sensor3 =  cs_12_3.capacitiveSensor(30);
  long Sensor4 =  cs_12_4.capacitiveSensor(30);
  long Sensor5 =  cs_12_5.capacitiveSensor(30);
  long Sensor6 =  cs_12_6.capacitiveSensor(30);
  long Sensor7 =  cs_12_7.capacitiveSensor(30);
  long Sensor8 =  cs_12_8.capacitiveSensor(30);
  long Sensor9 =  cs_12_9.capacitiveSensor(30);
  //long Sensor10 =  cs_12_10.capacitiveSensor(30);
  long Sensor11 =  cs_12_11.capacitiveSensor(30);

  if(counter < 30){
    sensor2_vals[counter] = Sensor2;
    sensor3_vals[counter] = Sensor3;
    sensor4_vals[counter] = Sensor4;
    sensor5_vals[counter] = Sensor5;
    sensor6_vals[counter] = Sensor6;
    sensor7_vals[counter] = Sensor7;
    sensor8_vals[counter] = Sensor8;
    sensor9_vals[counter] = Sensor9;
    counter++;


    //long sensorList[] = {Sensor2, Sensor3, Sensor4, Sensor5, Sensor6, Sensor7, Sensor8, Sensor9/*, Sensor10, Sensor11*/};
    /*for(int i = 0; i < 8; i++){
      Serial.print(sensorList[i]);
      Serial.print(" ");
    }
    Serial.println(Sensor11);
    */
  }
  

  long sensorList[] = {Sensor2, Sensor3, Sensor4, Sensor5, Sensor6, Sensor7, Sensor8, Sensor9/*, Sensor10, Sensor11*/};
  for(int i = 0; i < 8; i++){
    Serial.print(sensorList[i]);
    Serial.print(" ");
  }
  Serial.println(Sensor11);

  //Printing to see if we're doing thresholds right
  /*Serial.println("Sensor 2 difference: " + abs(average(sensor2_vals, counter) - Sensor2));
  Serial.println("Sensor 3 difference: " + abs(average(sensor4_vals, counter) - Sensor4));
  Serial.println("Sensor 5 difference: "+ abs(average(sensor5_vals, counter) - Sensor5));
  Serial.println("Sensor 6 difference: "+ abs(average(sensor6_vals, counter) - Sensor6));
  Serial.println("Sensor 7 difference: "+ abs(average(sensor7_vals, counter) - Sensor7));
  Serial.println("Sensor 8 difference: "+ abs(average(sensor8_vals, counter) - Sensor8));
  Serial.println("Sensor 9 difference: "+ abs(average(sensor9_vals, counter) - Sensor9));*/

  

  bool sensor2_high = (abs(average(sensor2_vals, counter) - Sensor2) > threshold);            
  bool sensor3_high = (abs(average(sensor3_vals, counter) - Sensor3) > threshold);   
  bool sensor4_high = (abs(average(sensor4_vals, counter) - Sensor4) > threshold);   
  bool sensor5_high = (abs(average(sensor5_vals, counter) - Sensor5) > threshold);   
  bool sensor6_high = (abs(average(sensor6_vals, counter) - Sensor6) > threshold);   
  bool sensor7_high = (abs(average(sensor7_vals, counter) - Sensor7) > threshold);   
  bool sensor8_high = (abs(average(sensor8_vals, counter) - Sensor8) > threshold);   
  bool sensor9_high = (abs(average(sensor9_vals, counter) - Sensor9) > threshold);   
  //bool sensor10_high = true;/*(Sensor10 > threshold); - just doing 0-8 for testing purposes*/



  //If the Cheerio is on NO SENSORS, it will print 0
  if(sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '0';
  }
  //If the Cheerio is on sensor 2, it will print 1
  else if (!sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '1';
  } 
  //If the Cheerio is on sensor 3, it will print 2
  else if (sensor2_high && !sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '2';
  } 
  //If the Cheerio is on sensor 4, it will print 3
  else if (sensor2_high && sensor3_high && !sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '3';
  } 
  //If the Cheerio is on sensor 5, it will print 4
  else if (sensor2_high && sensor3_high && sensor4_high && !sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '4';
  } 
  //If the Cheerio is on sensor 6, it will print 5
  else if (sensor2_high && sensor3_high && sensor4_high && sensor5_high && !sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '5';
  } 
  //If the Cheerio is on sensor 7, it will print 6
  else if (sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && !sensor7_high && sensor8_high && sensor9_high /*&& sensor10_high && sensor11_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '6';
  } 
  //If the Cheerio is on sensor 8, it will print 7
  else if (sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && !sensor8_high && sensor9_high /*&& sensor10_high && sensor11_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '7';
  } 
  //If the Cheerio is on sensor 9, it will print 8
 else if (sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && !sensor9_high /*&& sensor10_high && sensor11_high*/){
    digitalWrite(digPin, HIGH);
    num_input = '8';
  } 
  //If the Cheerio is on sensor 10, it will print 9
  //else if (sensor2_high && sensor3_high && sensor4_high && sensor5_high && sensor6_high && sensor7_high && sensor8_high && sensor9_high /*&& !sensor10_high && sensor11_high*/){
    //digitalWrite(digPin, HIGH);
    //num_input = '9';
  //} 
  
  
  //If I touch the copper tape, it will output the number onto the screen
  if(Sensor11 > threshold){
    Serial.print("Number input: ");
    Serial.print(num_input);
    Serial.println();
    Keyboard.write(num_input);
    delay(200);
    Keyboard.releaseAll();
  }
  /*if (Sensor2<=threshold && Sensor3<=threshold && Sensor4<=threshold && Sensor5<=threshold && Sensor6<=threshold && Sensor7<=threshold && Sensor8<=threshold && Sensor9<=threshold
  && Sensor10<=threshold && Sensor11<=threshold){
    digitalWrite(digPin, LOW);
  }*/
}