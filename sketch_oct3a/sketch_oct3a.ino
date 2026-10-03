
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

 pinMode(LEDPin, OUTPUT);
 digitalWrite(LEDPin, LOW);

}

void loop() {
  //go forward
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  analogWrite(enaLeft, 255);

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  analogWrite(enaRight, 255);
  
  //set speed for scoop
  analogWrite(enaScoop, 200);

  //delay(2000);

  //read from ultrasonic sensor
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
  if(blue > 65 && red < 80 && red > 60){
    Serial.println("\n\n=================Blue!=====================\n\n");   
  }
 
  Serial.print("\n");

  //if distance < 5 & blue < 80 then stop, back up, turn, drive a bit, turn again, drive, continue loop
  if(distance < 5 && blue < 80){
    Serial.println("detected garbage");
    Serial.println(distance);
    //stop
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    delay(500);

    //back up
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(500);

    //turn left
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(250);

    //go forward
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(250);

    //turn right
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(250);

    //go forward
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(1000);
    
    //turn right
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(250);

    //go forward
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(250);

    //turn left
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(250);

    totalTime += turnTime;

  }

  if(distance < 5 && int(blue) > 65 && red < 80 && red > 60){
    Serial.println("detected ball");
    //drive forward until ball is under scoop
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(500);

    //scoop the ball
    digitalWrite(scoopMotorPin1, HIGH);
    digitalWrite(scoopMotorPin2, LOW);
    delay(500);

    //stop
    digitalWrite(scoopMotorPin1, LOW);
    digitalWrite(scoopMotorPin2, LOW);
    delay(100);

    //return scoop to starting position
    digitalWrite(scoopMotorPin1, LOW);
    digitalWrite(scoopMotorPin2, HIGH);
    delay(500);

    collected++;
    totalTime += scoopTime;

  }

  runTime = startTime + millis();
  if(totalTime <= runTime){
    Serial.println("hit the end of the enclosure");
    //need to alternate turning directionsgi
    //stop
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    delay(500);

    //back up
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(500);

    //turn
    if(lastTurnDirection == 1){
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
      lastTurnDirection = 0;
    }else{
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
      lastTurnDirection = 1;
    }
    delay(250);

    //go forward
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);

    //turn
    if(lastTurnDirection == 1){
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
      lastTurnDirection = 0;
    }else{
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
      lastTurnDirection = 1;
    }
    delay(250);

    startTime = millis();

  }


  if(collected >= 3){
    Serial.println("collected all balls");
   //return to start
   //head to edge of box, follow it until back to start, 
   //turn into box

   //turn left
   digitalWrite(leftMotorPin1, HIGH);
   digitalWrite(leftMotorPin2, LOW);
   digitalWrite(rightMotorPin1, HIGH);
   digitalWrite(rightMotorPin2, LOW);

   //go forward
   digitalWrite(leftMotorPin1, HIGH);
   digitalWrite(leftMotorPin2, LOW);
   digitalWrite(rightMotorPin1, LOW);
   digitalWrite(rightMotorPin2, HIGH);

   //turn right
   digitalWrite(leftMotorPin1, LOW);
   digitalWrite(leftMotorPin2, HIGH);
   digitalWrite(rightMotorPin1, LOW);
   digitalWrite(rightMotorPin2, HIGH);

   //go forward
   digitalWrite(leftMotorPin1, HIGH);
   digitalWrite(leftMotorPin2, LOW);
   digitalWrite(rightMotorPin1, LOW);
   digitalWrite(rightMotorPin2, HIGH);

  }

}
