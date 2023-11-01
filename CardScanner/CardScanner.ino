#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

Adafruit_VL6180X vl = Adafruit_VL6180X();

//Pin connected to ST_CP of 74HC595
int latchPin = 17;

//Pin connected to SH_CP of 74HC595
int clockPin = 16;

////Pin connected to DS of 74HC595
int dataPin = 21;

byte x = 0b00000010;

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


  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

SerialComs();

}