#include "Servo.h"

// Servo A 30-60
Servo servoA;  // Servo A

// Servo B 0-90
Servo servoB;  // Servo B

// Servo C 160-30
Servo servoC;  // Servo C

// 0-180
Servo servoD;

// 0-180
Servo servoE;

void setup()
{
  Serial.begin(9600);
  servoA.attach(12);
  servoB.attach(11);
  servoC.attach(10);
  servoD.attach(9);
  servoE.attach(8);
}

void loop()
{
  // Lê o valor do Potenciometro
  int angleA = analogRead(0);
  int angleB = analogRead(1);
  int angleC = analogRead(2);
  int angleD = analogRead(3);
  int angleE = analogRead(4);

  // Mapeia o valor de 0 a 180 graus
  angleA = map(angleA, 0, 1023, 30, 100);
  angleB = map(angleB, 0, 1023, 0, 180);
  angleC = map(angleC, 0, 1023, 10, 100);
  angleD = map(angleD, 0, 1023, 100, 160);
  angleE = map(angleE, 0, 1023, 150, 180);

  // Repassa o angulo ao ServoWrite
  servoA.write(angleA);
  servoB.write(angleB);
  servoC.write(angleC);
  servoD.write(angleD);
  servoE.write(angleE);

  // Delay de 15ms para o Servo alcançar a posição
  delay(15);
}
