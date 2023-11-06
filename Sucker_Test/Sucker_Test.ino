
#include <ESP32Servo.h>

Servo myservo1;
Servo myservo2;

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo1.setPeriodHertz(50);  // standard 50 hz servo
  myservo2.setPeriodHertz(50);
  myservo1.attach(22, 1000, 2000);  // attaches the servo on pin 18 to the servo object
  myservo2.attach(23, 1000, 2000);
}

void loop() {

  myservo2.write(180);  // tell servo to go to position in variable 'pos'
  delay(500);

  myservo2.write(0);  // tell servo to go to position in variable 'pos'
  delay(2500);

  myservo1.write(180);  // tell servo to go to position in variable 'pos'
  delay(500);

  myservo1.write(0);  // tell servo to go to position in variable 'pos'
  delay(500);


}
