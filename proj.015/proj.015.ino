#include <Servo.h>
Servo servo1;
Servo servo2;

int distanceThreshold = 0;
int cm = 0;
int inches = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin (9600);       // initialize serial port
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(2, HIGH);
  
  servo1.attach(8);
  servo1.write(0);
  servo2.attach(10);
  servo2.write(0);
}

void loop()
{
  // set threshold distance to activate LEDs
  distanceThreshold = 300;
  // calculate the distance to the target in cm
  cm = 0.09923* readUltrasonicDistance(7, 6);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(inches);
  Serial.println("in");
  if (cm > distanceThreshold){
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(2, HIGH);
    noTone(4);
    ///ServoWrite
    servo1.write(0);
  }
  if (cm <= distanceThreshold && cm > distanceThreshold - 50) {
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(2, HIGH);
    noTone(4);
    ///ServoWrite
    servo1.write(0);
    servo2.write(0);
  }
  if (cm <= distanceThreshold - 50 && cm > distanceThreshold - 100) {
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    tone(4, 562,4512);
     ///ServoWrite
    servo1.write(0);
    servo2.write(0);
  }
  if (cm <= distanceThreshold - 100 && cm > distanceThreshold - 150) {
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
     digitalWrite(2, LOW);
    tone(4, 562,4512);
     ///ServoWrite
     servo1.write(150);
     delay(1000);
     servo1.write(0);
     servo2.write(60);
     delay(500);
    servo2.write(0);
  }
  if (cm <= distanceThreshold - 150 && cm > distanceThreshold - 170) {
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(2, LOW);
    tone(4, 562,4512);
    ///ServoWrite
    servo1.write(150);
    delay(1000);
    servo1.write(0);
    servo2.write(60);
    delay(500);
    servo2.write(0);
  }
  delay(100); // Wait for 100 millisecond(s)
}