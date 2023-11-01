#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

Adafruit_VL6180X vl = Adafruit_VL6180X();

const int numReadings = 10;

int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average

//Pin connected to ST_CP of 74HC595
int latchPin = 17;

//Pin connected to SH_CP of 74HC595
int clockPin = 16;

////Pin connected to DS of 74HC595
int dataPin = 21;

byte x = 0b00000010;

int count = 0;
long count1 = 0;

int range = 100;

unsigned long previousMicros = 0;

long interval = 200;

void setup() {

  delay(2000);

  Wire.begin(18, 23, 100000);

  Serial.begin(115200);

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

  //Serial.end();

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  if (count1 > 50000) {
   // interval = vl.readRange();
  //  interval = interval *2;
   // Serial.println(interval);
    count1 = 0;
  }
   // count1++;



  if (count > 8000) {
    bitSet(x, 2);
    bitSet(x, 6);
  }
  if (count > 16000) {
    bitClear(x, 2);
    bitClear(x, 6);
    count = 0;
  }



  unsigned long currentMicros = micros();

  if (currentMicros - previousMicros >= 300) {
    // save the last time you blinked the LED
    previousMicros = currentMicros;

    count++;

    digitalWrite(latchPin, LOW);

    bitSet(x, 7);
    bitSet(x, 1);    
    bitSet(x, 5);

    shiftOut(dataPin, clockPin, MSBFIRST, x);

    digitalWrite(latchPin, HIGH);

    digitalWrite(latchPin, LOW);

    bitClear(x, 7);
    bitClear(x, 1);    
    bitClear(x, 5);

    shiftOut(dataPin, clockPin, MSBFIRST, x);

    digitalWrite(latchPin, HIGH);
  }
}