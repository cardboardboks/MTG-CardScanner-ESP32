void XY_Pos(int XCard, int YCard) {

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

void Z_Pos(int ZCard) {
}