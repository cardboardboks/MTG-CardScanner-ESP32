void disableSteppers() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b11111111);
  digitalWrite(latchPin, HIGH);
}

void enalbeSteppers() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0b00000000);
  digitalWrite(latchPin, HIGH);
}

void stepX() {
  digitalWrite(latchPin, LOW);

  bitSet(ShiftRegOut, 7);
  bitSet(ShiftRegOut, 1);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);

  digitalWrite(latchPin, LOW);

  bitClear(ShiftRegOut, 7);
  bitClear(ShiftRegOut, 1);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);
}

void stepY() {
  digitalWrite(latchPin, LOW);

  bitSet(ShiftRegOut, 7);
  bitSet(ShiftRegOut, 5);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);

  digitalWrite(latchPin, LOW);

  bitClear(ShiftRegOut, 7);
  bitClear(ShiftRegOut, 5);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);
}

void stepXY() {
  digitalWrite(latchPin, LOW);

  bitSet(ShiftRegOut, 7);
  bitSet(ShiftRegOut, 5);
  bitSet(ShiftRegOut, 1);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);

  digitalWrite(latchPin, LOW);

  bitClear(ShiftRegOut, 7);
  bitClear(ShiftRegOut, 5);
  bitClear(ShiftRegOut, 1);

  shiftOut(dataPin, clockPin, MSBFIRST, ShiftRegOut);

  digitalWrite(latchPin, HIGH);
}

void stepZ() {
}