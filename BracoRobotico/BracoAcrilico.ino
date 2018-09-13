#include <Servo.h>

// Servo Garra 0-45
Servo servoGarra;  // Servo Garra

// Servo A 110-155
Servo servoA;  // Servo A

// Servo B 0-30
Servo servoB;  // Servo B

int angle;

void setup() {
  servoGarra.attach(11); // Porta Servo Garra
  servoA.attach(12); // Porta Servo A
  servoB.attach(13); // Porta Servo B
  Serial.begin(9600);
}

void loop() {
  // set the servo position
  servoGarra.write(45);
  servoA.write(110);
  servoB.write(0);

  //Se A == 100 B tem que ser 0
  //Se A >  110 B pode ser > 0

  /*float b = 0;

  for (int i = 110; i < 155; i++) {
    servoA.write(i);
    servoB.write(b);
    b += 1.5;
    delay(300);
  }

  servoGarra.write(0);
  delay(800);
  servoGarra.write(45);

  for (int i = 155; i > 110; i--) {
    servoA.write(i);
    servoB.write(b);
    b -= 1.5;
    delay(300);
  }

  servoGarra.write(0);
  delay(800);
  servoGarra.write(45);*/

}
