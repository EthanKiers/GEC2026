
#include "Adafruit_TCS34725.h"
#define commonAnode true
  
  int enaLeft = 10;
  int enaRight = 11;
  int leftMotorPin1 = 5;
  int leftMotorPin2 = 4;
  int rightMotorPin1 = 3;
  int rightMotorPin2 = 2;

  int colourSensorSDA = A4;
  int colourSensorSCL = A5;

  int trigPin = 6;
  int echoPin = 7;

  float duration, distance;

  int enaScoop = 9;
  int scoopMotorPin1 = 12;
  int scoopMotorPin2 = 13;

  int collected = 0;

  int lastTurnDirection = 1; //0 is left, 1 is right. should start by turning left, can be changed depending on the position of the satarting box

  int baseTime = 10000; //base amount of time to go from one side of the box to the other
  int turnTime = 5000; //time it takes to go around a piece of garbage
  int scoopTime = 2000; //time it takes to scoop up a ball

  int totalTime = baseTime;
  
  int startTime;
  int runTime;

  int LEDPin = A3;

  int linesCrossed = 0;
  bool lastDetectionLine = false;
  bool lastDetectionTile = false;
  bool currentDetectionLine = false;
  bool currentDetectionTile = false;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
void setup() {
  pinMode(enaLeft, OUTPUT);
  pinMode(enaRight, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(enaScoop, OUTPUT);
  pinMode(scoopMotorPin1, OUTPUT);
  pinMode(scoopMotorPin2, OUTPUT);
  // delay(2000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
 
 startTime = millis();

 //pinMode(LEDPin, OUTPUT);
 //digitalWrite(LEDPin, LOW);

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  analogWrite(enaRight, 90);

  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  analogWrite(enaLeft, 90);
  delay(1);
  analogWrite(enaScoop, 80);
  digitalWrite(scoopMotorPin1, HIGH);
  digitalWrite(scoopMotorPin2, LOW);
  //delay(1000);
  //offScoop(100);

}

void loop() {
  //go forward 3 tiles
  forward(3100);
  // digitalWrite(rightMotorPin1, LOW);
  // digitalWrite(rightMotorPin2, HIGH);
  // digitalWrite(leftMotorPin1, LOW);
  // digitalWrite(leftMotorPin2, HIGH);

  // //set speed for scoop


  // //delay(2000);

  //read from ultrasonic sensor
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // duration = pulseIn(echoPin, HIGH);
  // distance = (duration*.0343)/2;
  // Serial.print("Distance: ");
  // Serial.println(distance);
  // delay(100);

  // //read from colour sensor
  // float red, green, blue;
  // tcs.setInterrupt(false);  // turn on LED
  // delay(60);  // takes 50ms to read
  // tcs.getRGB(&red, &green, &blue);
  // tcs.setInterrupt(true);  // turn off LED
 
  // Serial.print("R:\t"); Serial.print(int(red));
  // Serial.print("\tG:\t"); Serial.print(int(green));
  // Serial.print("\tB:\t"); Serial.print(int(blue));
  // //for a value to be blue, the blue value should be greater than 90
  // // if(blue > 65 && red < 80 && red > 60){
  // //   Serial.println("\n\n=================Blue!=====================\n\n");   
  // // }

  // if(red < 130 && green < 140 && blue < 120){
  //   currentDetectionTile = true;
  // }else{
  //   currentDetectionLine = true;
  // }

  // if(currentDetectionTIle == lastDetectionLine){
  //   linesCrossed++;
  // }
 
  // Serial.print("\n");

  // if(distance < 5){
  //   Serial.println("detected ball");
  //   //drive forward until ball is under scoop
  //   digitalWrite(leftMotorPin1, HIGH);
  //   digitalWrite(leftMotorPin2, LOW);
  //   digitalWrite(rightMotorPin1, LOW);
  //   digitalWrite(rightMotorPin2, HIGH);
  //   delay(500);

  //   //scoop the ball
  //   digitalWrite(scoopMotorPin1, HIGH);
  //   digitalWrite(scoopMotorPin2, LOW);
  //   delay(500);

  //   //stop
  //   digitalWrite(scoopMotorPin1, LOW);
  //   digitalWrite(scoopMotorPin2, LOW);
  //   delay(100);

  //   //return scoop to starting position
  //   digitalWrite(scoopMotorPin1, LOW);
  //   digitalWrite(scoopMotorPin2, HIGH);
  //   delay(500);

  //   digitalWrite(rightMotorPin1, LOW);
  //   digitalWrite(rightMotorPin2, HIGH);
  //   analogWrite(enaRight, 150);

  //   digitalWrite(leftMotorPin1, HIGH);
  //   digitalWrite(leftMotorPin2, LOW);
  //   analogWrite(enaLeft, 150);

  //   collected++;
  //   totalTime += scoopTime;

  // }

  //turn right
  right(1100);

  //drive forward 1 tile
  forward(1300);

  //stop
  offWheels(100);

  //scoop
  scoop(1000);

  //stop
  offScoop(100);

  //return scoop to starting position
  returnScoop(1000);

  //turn right
  right(1490);

  //drive forward 2 tiles
  forward(2350);

  //stop
  offWheels(100);

  //scoop
  scoop(1000);

  //stop
  offScoop(100);

  //return scoop to starting position
  returnScoop(1000);
  //-----------------
  //turn left
  left(1600);
  //drive forward 1 tile
  forward(500);
  //turn right
  right(800);
  //drive forward 1 tile
  forward(500);
  //turn left
  left(800);
  //drive forward 1 tile
  forward(500);
  //stop
  offWheels(100);
  //scoop
  scoop(1000);
  offScoop(100);
  returnScoop(1000);
  //turn right
  right(800);
  //go forward 1 tile
  forward(500);
  //turn right
  right(800);

  //drive forward 3 tiles
  forward(1500);
  //turn right
  right(800);
  //drive forward 4 tiles
  forward(2000);
  offWheels(100);
// lastDetectionTile = currentDetectionTile;
// lastDetectionLine = currentDetectionLine;
  while(1){
    delay(100);
  }
}


void forward(int time){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  delay(time);
}

void right(int time){
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  delay(time);
}

void left(int time){
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  delay(time);
}

void reverse(int time){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  delay(time);
}

void scoop(int time){
  digitalWrite(scoopMotorPin1, LOW);
  digitalWrite(scoopMotorPin2, HIGH);
  delay(time);
}

void returnScoop(int time){
  digitalWrite(scoopMotorPin1, HIGH);
  digitalWrite(scoopMotorPin2, LOW);
  delay(time);
}

void offWheels(int time){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
}

void offScoop(int time){
  digitalWrite(scoopMotorPin1, LOW);
  digitalWrite(scoopMotorPin2, LOW);
  delay(time);
}


