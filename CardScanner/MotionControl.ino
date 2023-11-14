void XY_Pos(float XCard, float YCard) {

  int accelTarget = 0;

  float accelX = 1;
  float accelY = 1;

  float accelXOut = 1;
  float accelYOut = 1;
  float accelMaster = 0;

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
  float shortStepIncCount = 0;
  float longStepInc = 0;
  float longStepIncCount = 0;

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

  /*

  if (XCardTarget > YCardTarget) {




    if (XCardTarget == 0 || YCardTarget == 0) {
      XLong = 1;
      YShort = 1;
      // shortStepInc = lcm(YCardTarget, XCardTarget) / YCardTarget;
      longStepTarget = XCardTarget;
    }



  }

  if (YCardTarget > XCardTarget) {
    if (YCardTarget == 0 || XCardTarget == 0) {
      YLong = 1;
      XShort = 1;
      //shortStepInc = lcm(YCardTarget, XCardTarget) / XCardTarget;
      longStepTarget = YCardTarget;
    }
  }


  */


  startXPos = StepXPos;
  endXPos = XCard;
  startYPos = StepYPos;
  endYPos = YCard;

  //Long X Move
  if (startXPos - endXPos != 0 && startYPos - endYPos != 0) {
    if ((lcm(YCardTarget, XCardTarget) / XCardTarget) < (lcm(YCardTarget, XCardTarget) / YCardTarget)) {
      XLong = 1;
      YShort = 1;
      longStepInc = lcm(YCardTarget, XCardTarget) / XCardTarget;
      shortStepInc = lcm(YCardTarget, XCardTarget) / YCardTarget;
      longStepTarget = XCardTarget;
    }
  }

  //Long Y Move
  if (startXPos - endXPos != 0 && startYPos - endYPos != 0) {
    if ((lcm(YCardTarget, XCardTarget) / XCardTarget) > (lcm(YCardTarget, XCardTarget) / YCardTarget)) {
      YLong = 1;
      XShort = 1;
      longStepInc = lcm(YCardTarget, XCardTarget) / YCardTarget;
      shortStepInc = lcm(YCardTarget, XCardTarget) / XCardTarget;
      longStepTarget = YCardTarget;
    }
  }

  //Pure Diagonal Move
  if (startXPos - endXPos != 0 && startYPos - endYPos != 0) {
    if ((lcm(YCardTarget, XCardTarget) / XCardTarget) == 1 && (lcm(YCardTarget, XCardTarget) / YCardTarget) == 1) {
      XLong = 1;
      YShort = 1;
      longStepInc = 1;
      shortStepInc = 1;
      longStepTarget = XCardTarget;
    }
  }

  //Pure X move
  if (startYPos - endYPos == 0 && startXPos - endXPos != 0) {
    XLong = 1;
    longStepTarget = XCardTarget;
  }

  //Pure Y move
  if (startXPos - endXPos == 0 && startYPos - endYPos != 0) {
    YLong = 1;
    longStepTarget = YCardTarget;
  }

  enalbeSteppers();

  //Loop to run through until movment is complete
  while (longStep < longStepTarget) {

    unsigned long currentMicrosStep = micros();
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

      if (fromYStart < fromYEnd) {
        accelY -= .005;
      }

      if (fromYEnd < fromYStart) {
        accelY += .005;
      }

      if (fromXStart < fromXEnd) {
        accelX -= .005;
      }

      if (fromXEnd < fromXStart) {
        accelX += .005;
      }
    }

    accelXOut = accelX;
    accelYOut = accelY;

    if (XLong == 1) {
      accelMaster = accelXOut;
    }

    if (YLong == 1) {
      accelMaster = accelYOut;
    }

    accelMaster *= 1500;

    if (accelMaster < 50) {
      accelMaster = 50;
    }
    if (accelMaster > 1500) {
      accelMaster = 1500;
    }

    if (currentMicrosStep - previousMicrosStep >= accelMaster) {
      previousMicrosStep = currentMicrosStep;


      if (XLong == 1) {
        stepX();
        longStep++;
        longStepIncCount += longStepInc;
        StepXPos += StepXDir;
      }
      if (YLong == 1) {
        stepY();
        longStep++;
        longStepIncCount += longStepInc;
        StepYPos += StepYDir;
      }

      if (longStepIncCount >= shortStepInc) {

        longStepIncCount -= shortStepInc;

        if (XShort == 1) {
          stepX();
          StepXPos += StepXDir;
        }
        if (YShort == 1) {
          stepY();
          StepYPos += StepYDir;
        }
      }


      // Serial.print(StepXPos);
      // Serial.print("\t");
      //Serial.println(StepYPos);
    }
  }
  disableSteppers();
}
