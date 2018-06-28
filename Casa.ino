#include <Servo.h>

int ledPin = 7; //Led no pino 7
int ldrPin = 0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
int sensorPin = 5; //the analog pin the TMP36's Vout (sense) pin is connected to

#define SERVO 6 // Porta Digital 6 PWM

Servo s; // Variável Servo
int pos; // Posição Servo

void SensorTemperatura() {
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");

}

void ServoMotor() {

  for (pos = 0; pos < 90; pos++)
  {
    s.write(pos);
    delay(15);
  }
  delay(1000);
  for (pos = 90; pos >= 0; pos--)
  {
    s.write(pos);
    delay(15);
  }

}

void SensorLuz() {

  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  //se o valor lido for maior que 500, liga o led
  if (ldrValor >= 800) digitalWrite(ledPin, HIGH);
  // senão, apaga o led
  else digitalWrite(ledPin, LOW);
  //imprime o valor lido do LDR no monitor serial
  Serial.println(ldrValor);

}


void setup() {
  pinMode(ledPin, OUTPUT); //define a porta 7 como saída
  Serial.begin(9600); //Inicia a comunicação serial
  s.attach(SERVO);
  s.write(0); // Inicia motor posição zero

}

void loop() {

  SensorLuz();
  SensorTemperatura();
  ServoMotor();
  delay(1000);

}
