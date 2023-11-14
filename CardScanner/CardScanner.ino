#include <Wire.h>
#include "Adafruit_VL6180X.h"
//#include <ESP32Servo.h>

Adafruit_VL6180X vl = Adafruit_VL6180X();
//Servo myservo1;
//Servo myservo2;

//Stepper Location
float StepXPos = 0.0;
float StepYPos = 0.0;
float StepZPos = 0.0;

int StepXPermm = 200;
int StepYPermm = 200;
int StepZPermm = 200;

//Pin connected to ST_CP of 74HC595
int latchPin = 17;

//Pin connected to SH_CP of 74HC595
int clockPin = 16;

////Pin connected to DS of 74HC595
int dataPin = 21;

byte ShiftRegOut = 0b00000000;

int range = 100;

unsigned long previousMicrosStep = 0;
unsigned long previousMicrosAccl = 0;

float speed = 500;
float intervalX = 400;
float intervalY = 400;
float intervalAccl = 1000;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];  // temporary array for use when parsing

float cardX = 0.0;
float cardY = 0.0;

int StepXDir = 0;
int StepYDir = 0;

int stepSpeed = 0;

boolean newData = false;

void setup() {

  delay(2000);

  Wire.begin(18, 23, 100000);

  Serial.begin(115200);

  // ESP32PWM::allocateTimer(0);
  // ESP32PWM::allocateTimer(1);
  // ESP32PWM::allocateTimer(2);
  //  ESP32PWM::allocateTimer(3);
  // myservo1.setPeriodHertz(50);
  // myservo2.setPeriodHertz(50);      // standard 50 hz servo
  //  myservo1.attach(34, 1000, 2200);  // attaches the servo object
  // myservo2.attach(35, 1000, 2000);

  // wait for serial port to open on native usb devices
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL6180x test!");
  if (!vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1)
      ;
  }
  Serial.println("Sensor found!");


  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  disableSteppers();
  // enalbeSteppers();
}

void loop() {

  /*
  int testX = random(-8000, 8000);
  int testY = random(-8000, 8000);

  XY_Pos(testX, testY);
  */

  recvWithStartEndMarkers();

  //Serial.println("Y");
  //delay(2000);

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    showParsedData();
    newData = false;
  }
}