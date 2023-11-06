void XY_Pos(float XCard, float YCard) {
  int accelTarget = 0;
  float accel = 1;

  int accelerate = 1;
  int decelerate = 0;

  float startXPos = 0;
  float endXPos = 0;
  float startYPos = 0;
  float endYPos = 0;

  enalbeSteppers();

  if (XCard - StepXPos > 0) {
    bitSet(ShiftRegOut, 2);
    StepXDir = 1;
  } else if (XCard - StepXPos < 0) {
    bitClear(ShiftRegOut, 2);
    StepXDir = -1;
  } else {
    StepXDir = 0;
  }

  if (YCard - StepYPos > 0) {
    bitSet(ShiftRegOut, 6);
    StepYDir = 1;
  } else if (YCard - StepYPos < 0) {
    bitClear(ShiftRegOut, 6);
    StepYDir = -1;
  } else {
    StepYDir = 0;
  }
  float XCardTarget = XCard - StepXPos;
  float YCardTarget = YCard - StepYPos;

  if (XCardTarget < 0) {
    XCardTarget *= -1;
  }
  if (YCardTarget < 0) {
    YCardTarget *= -1;
  }

  if (XCardTarget > YCardTarget) {
    accelTarget = 1;
    if (XCardTarget == 0 || YCardTarget == 0) {
      intervalX = 400.0;
      intervalY = 400.0;
    } else {
      intervalX = 400;
      intervalY = 400 * (XCardTarget / YCardTarget);
    }
  }

  if (YCardTarget > XCardTarget) {
    accelTarget = 2;
    if (YCardTarget == 0 || XCardTarget == 0) {
      intervalX = 400.0;
      intervalY = 400.0;
    } else {
      intervalX = 400.0 * (YCardTarget / XCardTarget);
      intervalY = 400.0;
    }
  }

  if (XCardTarget == YCardTarget) {
    accelTarget = 1;
    intervalX = 400.0;
    intervalY = 400.0;
  }

  while (StepXDir != 0 || StepYDir != 0) {

    unsigned long currentMicrosX = micros();
    unsigned long currentMicrosY = micros();

    if (XCard - StepXPos != 0) {
      if (currentMicrosX - previousMicrosX >= (intervalX)*1) {
        previousMicrosX = currentMicrosX;

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

        StepXPos += StepXDir;
      }
    } else {
      StepXDir = 0;
    }


    if (YCard - StepYPos != 0) {
      if (currentMicrosY - previousMicrosY >= (intervalY)*1) {
        previousMicrosY = currentMicrosY;

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

        StepYPos += StepYDir;
      }
    } else {
      StepYDir = 0;
    }
  }
  disableSteppers();
}







void Z_Pos(int ZCard) {
}

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