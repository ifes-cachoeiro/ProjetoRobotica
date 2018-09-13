#include <Servo.h>

// Servo Garra 0-60
Servo servoGarra;  // Servo Garra

// 0-55-180
Servo servoA;

// 0-55-80
Servo servoB;

// 150-80
Servo servoC;

// 0-180
Servo servoD;

// 0-180
Servo servoE;
int angle;

void setup() {
  servoA.attach(10);
  servoE.attach(12); // Porta Servo Garra
  servoD.attach(11);
  servoB.attach(8);
  servoC.attach(9);
  Serial.begin(9600);
}

void loop() {
  // set the servo position
  servoE.write(80);
  servoD.write(80);
  servoB.write(0);
  servoC.write(80);
  servoA.write(0);
}
