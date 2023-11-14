/*
void XY_Pos(float XCard, float YCard) {

  int accelTarget = 0;

  float accelX = 1;
  float accelY = 1;

  float accelXOut = 1;
  float accelYOut = 1;

  float startXPos = 0;
  float endXPos = 0;
  float startYPos = 0;
  float endYPos = 0;

  float fromXStart = 0;
  float fromXEnd = 0;
  float fromYStart = 0;
  float fromYEnd = 0;

  int acclDur = 500;

  float XCardTarget = XCard - StepXPos;
  float YCardTarget = YCard - StepYPos;

  int XLong = 0;
  int XShort = 0;
  int YLong = 0;
  int YShort = 0;

  float longStep = 0;
  float shortStep = 0;

  float longStepTarget = 0;
  float shortStepInc = 0;
  float longStepInc = 0;

  //Set X Stepper direction pin to the required direction
  if (XCardTarget > 0) {
    bitSet(ShiftRegOut, 2);
    StepXDir = 1;
  } else if (XCardTarget < 0) {
    bitClear(ShiftRegOut, 2);
    StepXDir = -1;
  } else {
    StepXDir = 0;
  }
  //Set Y Stepper direction pin to the required direction
  if (YCardTarget > 0) {
    bitSet(ShiftRegOut, 6);
    StepYDir = 1;
  } else if (YCardTarget < 0) {
    bitClear(ShiftRegOut, 6);
    StepYDir = -1;
  } else {
    StepYDir = 0;
  }

  //Make both CardTargets positive for easier use latter on
  if (XCardTarget < 0) {
    XCardTarget *= -1;
  }
  if (YCardTarget < 0) {
    YCardTarget *= -1;
  }

  if (XCardTarget > YCardTarget) {
    if (XCardTarget == 0 || YCardTarget == 0) {
      XLong = 1;
      YShort = 1;
      longStepTarget = XCardTarget;
    }
  }

  if (YCardTarget > XCardTarget) {
    if (YCardTarget == 0 || XCardTarget == 0) {
      YLong = 1;
      XShort = 1;
      longStepTarget = YCardTarget;
    }
  }

  if (XCardTarget == YCardTarget) {
    XLong = 1;
    YShort = 1;
    longStepTarget = XCardTarget;
  }

  startXPos = StepXPos;
  endXPos = XCard;
  startYPos = StepYPos;
  endYPos = YCard;

  Serial.print("X ");
  Serial.print(XCardTarget);
  Serial.print(" Y ");
  Serial.println(YCardTarget);

  if (YCardTarget > 0 && XCardTarget > 0) {
    Serial.print("  LCD ");
    Serial.print(lcm(YCardTarget, XCardTarget));
    Serial.print("X ");
    Serial.print(lcm(YCardTarget, XCardTarget) / XCardTarget);
    Serial.print(" Y ");
    Serial.println(lcm(YCardTarget, XCardTarget) / YCardTarget);
  } else {
    Serial.println(" one is zero");
  }

  enalbeSteppers();

  //Loop to run through until movment is complete
  while (longStep < longStepTarget) {

    unsigned long currentMicrosStep = micros();

    if (currentMicrosStep - previousMicrosStep >= 600) {
      previousMicrosStep = currentMicrosStep;

      if (XLong == 1) {
        stepX();
        StepXPos += StepXDir;
      } else {
        stepY();
        StepYPos += StepYDir;
      }
      longStep++;
      longStepInc++;

      if (shortStepInc <= longStepInc) {

        longStepInc = 0;

        if (XShort == 1) {
          stepX();
          StepYPos += StepXDir;
        } else {
          stepY();
          StepXPos += StepYDir;
        }
      }
      Serial.print(StepXPos);
      Serial.print("\t");
      Serial.println(StepYPos);
    }
  }
  disableSteppers();
}


void Z_Pos(int ZCard) {
}

//Acceleration stuff not needed yet
/*
    unsigned long currentMicrosAccl = micros();

    if (currentMicrosAccl - previousMicrosAccl >= intervalAccl) {
      previousMicrosAccl = currentMicrosAccl;

      //check if the distance being traveled is less then the acceleration distance and halve it so the acceleration and deacelrtion dont cancel out
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
        accelY -= .05;
      }

      if (fromYEnd < acclDur && fromYStart > acclDur) {
        accelY += .05;
      }


      if (fromXStart < acclDur && fromXEnd > acclDur) {
        accelX -= .05;
      }

      if (fromXEnd < acclDur && fromXStart > acclDur) {
        accelX += .05;
      }
    }

    accelXOut = accelX;
    accelYOut = accelY;


    if (accelXOut < .1) {
      accelXOut = .1;
    }
    if (accelXOut > 10) {
      accelXOut = 10;
    }

    if (accelYOut < .1) {
      accelYOut = .1;
    }
    if (accelYOut > 10) {
      accelYOut = 10;
    }

    /*
    Serial.print("X ");
    Serial.print(fromXEnd);
    Serial.print("  Y ");
    Serial.println(fromYEnd);


    Serial.print( intervalX * accelXOut);
    Serial.print("\t");
    Serial.println(intervalY * accelXOut);

    Serial.print("From Start ");
    Serial.print(fromXStart);
    Serial.print("  To End ");
    Serial.print(fromXEnd);
    Serial.print("  Accel ");
    Serial.println(accelXOut);

    Serial.print("From Start ");
    Serial.print(fromXStart);
    Serial.print("  To End ");
    Serial.println(fromXEnd);
    





      Serial.print("Xs ");
  Serial.print(startXPos);
  Serial.print(" Ye ");
  Serial.println(endXPos);
  Serial.print("Ys ");
  Serial.print(startYPos);
  Serial.print(" Ye ");
  Serial.println(endYPos);

  Serial.print("X ");
  Serial.print(XCardTarget);
  Serial.print(" Y ");
  Serial.println(YCardTarget);

  if (startXPos - endXPos != 0 && startYPos - endYPos != 0) {
    Serial.print("  LCD ");
    Serial.print(lcm(YCardTarget, XCardTarget));
    Serial.print("X ");
    Serial.print(lcm(YCardTarget, XCardTarget) / XCardTarget);
    Serial.print(" Y ");
    Serial.println(lcm(YCardTarget, XCardTarget) / YCardTarget);
  } else {
    Serial.println("one is zero");
  }

  Serial.print("longStepTarget ");
  Serial.print(longStepTarget);
  Serial.print("  shortStepInc ");
  Serial.println(shortStepInc);



        if (fromYStart < acclDur && fromYEnd > acclDur) {
        accelY -= .025;
      }

      if (fromYEnd < acclDur && fromYStart > acclDur) {
        accelY += .025;
      }


      if (fromXStart < acclDur && fromXEnd > acclDur) {
        accelX -= .025;
      }

      if (fromXEnd < acclDur && fromXStart > acclDur) {
        accelX += .025;
      }
  */
