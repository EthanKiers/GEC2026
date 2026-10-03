
#include "Adafruit_TCS34725.h"
#define commonAnode true
  
  int enaLeft = 10;
  int enaRight = 11;
  int leftMotorPin1 = 2;
  int leftMotorPin2 = 3;
  int rightMotorPin1 = 4;
  int rightMotorPin2 = 5;

  int colourSensorSDA = A4;
  int colourSensorSCL = A5;

  int trigPin = 6;
  int echoPin = 7;

  float duration, distance;
 
};   


  //const byte pinLED = A3; // for led

// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  pinMode(enaLeft, OUTPUT);
  pinMode(enaRight, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  // pinMode (pinLED, OUTPUT); //led
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
 

}
//R:	90	G:	86	B:	63
//R:	63	G:	88	B:	93

void loop() {
  //delay(1000);

  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

  analogWrite(enaLeft, 200);

  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);

  analogWrite(enaRight, 200);
  delay(2000);

  //forward
  //backward
  //left
  //right

  //read from ultrasonic sensor
  //if at wall, back up, turn  to one side, move a bit, turn again, head back
  //constantly scan from sensor to see what colour things are

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

//read from colour sensor
  float red, green, blue;
  tcs.setInterrupt(false);  // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // turn off LED
 
  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));
  //for a value to be blue, the blue value should be greater than 90
 
  Serial.print("\n");

//   //if distance < 5 & blue < 80 then stop, back up, turn, drive a bit, turn again, drive, continue loop
//   if(distance < 5 && blue < 80){
//     //stop
//     digitalWrite(leftMotorPin1, LOW);
//     digitalWrite(leftMotorPin2, LOW);
//     digitalWrite(rightMotorPin1, LOW);
//     digitalWrite(rightMotorPin2, LOW);
//     delay(500);

//     //back up
//     digitalWrite(leftMotorPin1, LOW);
//     digitalWrite(leftMotorPin2, LOW);
//     digitalWrite(rightMotorPin1, LOW);
//     digitalWrite(rightMotorPin2, LOW);
//     delay(500);

//     //turn left
//     digitalWrite(leftMotorPin1, LOW);
//     digitalWrite(leftMotorPin2, LOW);
//     digitalWrite(rightMotorPin1, LOW);
//     digitalWrite(rightMotorPin2, LOW);

//     //go forward

//     //turn left again

  



}
