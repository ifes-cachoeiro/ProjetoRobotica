#include "Servo.h"

// Servo Garra 0-45
Servo servoGarra;  // Servo Garra

// Servo A 110-155
Servo servoA;  // Servo A

// Servo B 0-30
Servo servoB;  // Servo B

void setup()
{
  Serial.begin(9600);
  servoGarra.attach(11); // Porta Servo Garra
  servoA.attach(12); // Porta Servo A
  servoB.attach(13); // Porta Servo B
}

void loop()
{
  // Lê o valor do Potenciometro
  int angleGarra = analogRead(0);
  int angleA = analogRead(1);
  int angleB = analogRead(2);

  // Mapeia o valor de 0 a 180 graus
  angleGarra = map(angleGarra, 0, 1023, 0, 45);
  angleA = map(angleA, 0, 1023, 110, 155);
  angleB = map(angleB, 0, 1023, 0, 30);

  // Repassa o angulo ao ServoWrite
  servoGarra.write(angleGarra);
  servoA.write(angleA);
  servoB.write(angleB);

  // Delay de 15ms para o Servo alcançar a posição
  delay(15);
}
