/* Name: Sarah Huang, Christian Tongate
 * Date: 4/1/24
*/

#include <Arduino_LSM6DS3.h>
float x, y, z;
int degree = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  pinMode(10, OUTPUT);
  Serial.println("\n---Kick the car!---");
}

//Reads acceleration and then continues to drive depending on the force of the kick
void loop() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }
  degree = calculateDegree(x);
  if(degree != 0){
    drive(degree);
    degree = 0;
    Serial.println("\nReady for next kick...");
  } 
  delay(200);
}

//Calculates the degrees in the x axis that the accelerometer is moving
int calculateDegree(float x){
  int degreesX = 0;
  if (x > 0.2) {
    x = 100 * x;
    degreesX = map(x, 0, 97, 0, 90);
  }
  else if (x < -0.2) {
    x = 100 * x;
    degreesX = map(x, 0, -100, 0, 90);
 }
 return degreesX;
}

//Using the calcualted degrees, the motor spins for however long the driveTime is and stops.
void drive(int power) {
  Serial.print("Power Level: ");
  Serial.println(power);

  float driveTime = power * 100;
  Serial.print("Driving Time: ");
  Serial.print(driveTime/1000.0);
  Serial.println(" seconds");

  digitalWrite(10, HIGH);
  delay(driveTime); //not executing any code while it's driving
  digitalWrite(10, LOW);
}
