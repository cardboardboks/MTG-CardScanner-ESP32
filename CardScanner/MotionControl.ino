void XY_Pos(float XCard, float YCard) {

  int accelTarget = 0;

  float accelX = 1;
  float accelY = 1;

  int accelerate = 1;
  int decelerate = 0;

  float startXPos = 0;
  float endXPos = 0;
  float startYPos = 0;
  float endYPos = 0;

  float fromXStart = 0;
  float fromXEnd = 0;
  float fromYStart = 0;
  float fromYEnd = 0;

  int acclDur = 250;

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
    accelTarget = 2;
    if (XCardTarget == 0 || YCardTarget == 0) {
      intervalX = 400.0;
      intervalY = 400.0;
    } else {
      intervalX = 400;
      intervalY = 400 * (XCardTarget / YCardTarget);
    }
  }

  if (YCardTarget > XCardTarget) {
    accelTarget = 1;
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

  startXPos = StepXPos;
  endXPos = XCard;
  startYPos = StepYPos;
  endYPos = YCard;

  while (StepXDir != 0 || StepYDir != 0) {

    unsigned long currentMicrosX = micros();
    unsigned long currentMicrosY = micros();
    unsigned long currentMicrosAccl = micros();

    if (currentMicrosAccl - previousMicrosAccl >= intervalAccl) {
      previousMicrosAccl = currentMicrosAccl;

      //  if (accelTarget == 1) {
      if (StepYPos - startYPos < 0) {
        fromYStart = (StepYPos - startYPos) * -1;
      } else {
        fromYStart = (StepYPos - startYPos);
      }

      if (StepYPos - endYPos < 0) {
        fromYEnd = (StepYPos - endYPos) * -1;
      } else {
        fromYEnd = (StepYPos - endYPos);
      }

      if (fromYStart < acclDur && fromYEnd > acclDur) {
        accelY -= .0075;
      }

      if (fromYEnd < acclDur && fromYStart > acclDur) {
        accelY += .0075;
      }
      //  }

      //  if (accelTarget == 2) {
      if (StepXPos - startXPos < 0) {
        fromXStart = (StepXPos - startXPos) * -1;
      } else {
        fromXStart = (StepXPos - startXPos);
      }

      if (StepXPos - endXPos < 0) {
        fromXEnd = (StepXPos - endXPos) * -1;
      } else {
        fromXEnd = (StepXPos - endXPos);
      }

      if (fromXStart < acclDur && fromXEnd > acclDur) {
        accelX -= .0075;
      }

      if (fromXEnd < acclDur && fromXStart > acclDur) {
        accelX += .0075;
      }
    }
    //  }

    /*
    Serial.print("From Start ");
    Serial.print(fromXStart);
    Serial.print("  To End ");
    Serial.print(fromXEnd);
    Serial.print("  Accel ");
    Serial.println(accel);


    Serial.print("From Start ");
    Serial.print(fromXStart);
    Serial.print("  To End ");
    Serial.println(fromXEnd);
    */

      if (accelX < .1) {
        accelX = .1;
      }
      if (accelX > 1) {
        accelX = 1;
      }

      if (accelY < .1) {
        accelY = .1;
      }
      if (accelY > 1) {
        accelY = 1;
      }

      // Serial.println(accel);

      if (XCard - StepXPos != 0) {
        if (currentMicrosX - previousMicrosX >= (intervalX)*accelX) {
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
        if (currentMicrosY - previousMicrosY >= (intervalY)*accelY) {
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