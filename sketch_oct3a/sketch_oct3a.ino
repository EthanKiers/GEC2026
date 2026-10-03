#include "Wire.h"
#include "Adafruit_TCS34725.h"
#define commonAnode true
  
  int leftMotorPin1 = 2;
  int leftMotorPin2 = 3;
  int rightMotorPin1 = 4;
  int rightMotorPin2 = 5;

  int colourSensorSDA = A4;
  int colourSensorSCL = A5;

  //const byte pinLED = A3; // for led

//   // our RGB -> eye-recognized gamma color
// byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  // pinMode(leftMotorPin1, OUTPUT);
  // pinMode(leftMotorPin2, OUTPUT);
  // pinMode(rightMotorPin1, OUTPUT);
  // pinMode(rightMotorPin2, OUTPUT);
  // pinMode (pinLED, OUTPUT); //led

  Serial.begin(9600);
 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
 
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
 
    // if (commonAnode) {
    //   gammatable[i] = 255 - x;
    // } else {
    //   gammatable[i] = x;
    // }
    //Serial.println(gammatable[i]);
  }

}
//R:	90	G:	86	B:	63
//R:	63	G:	88	B:	93

void loop() {
  delay(1000);

  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, HIGH);

  //read from ultrasonic sensor

//read from colour sensor
  float red, green, blue;
  tcs.setInterrupt(false);  // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // turn off LED
 
  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));
  //blue > 90
 
  Serial.print("\n");
 



}
