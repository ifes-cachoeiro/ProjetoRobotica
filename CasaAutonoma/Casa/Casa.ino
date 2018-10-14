#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
char st[20];

int ldrPin = 0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
int sensorPin = 5; //Porta analogica sensor Temperatura
int motorDC = 12; // Porta do Motor DC

Servo s; // Variável Servo
int pos; // Posição Servo

#define SERVO 6 // Porta Digital 6 PWM

float armazenavalor;

int pinoled1 = 5;
int pinoled2 = 6;
int pinoled3 = 7;
int pinoled4 = 8;

void SensorLuz() {

  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  //se o valor lido for maior que 500, liga o led

  if (ldrValor >= 800) {
    digitalWrite(pinoled1, HIGH);
    digitalWrite(pinoled2, HIGH);
    digitalWrite(pinoled3, HIGH);
    digitalWrite(pinoled4, HIGH);
  } else {
    digitalWrite(pinoled1, LOW);
    digitalWrite(pinoled2, LOW);
    digitalWrite(pinoled3, LOW);
    digitalWrite(pinoled4, LOW);
  }

  //imprime o valor lido do LDR no monitor serial
  Serial.println(ldrValor);

}

void SensorTemperatura() {

  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");

  if (temperatureC > 25) {
    digitalWrite(motorDC, HIGH);
  } else {
    digitalWrite(motorDC, LOW);
  }

}

void ServoMotor() {

  for (pos = 0; pos < 90; pos++) {
    s.write(pos);
    delay(15);
  }

  delay(1000);

  for (pos = 90; pos >= 0; pos--) {
    s.write(pos);
    delay(15);
  }

}

void rfidVerificar() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "ED 78 03 CA") {
    Serial.print("Acesso liberado!");
    delay(3000);
    mensageminicial();
    ServoMotor();
  }
}

void mensageminicial() {
  Serial.println("Aproxime Seu Cartao!");
}


void setup() {
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  pinMode(pinoled1, OUTPUT);
  pinMode(pinoled1, OUTPUT);
  pinMode(pinoled3, OUTPUT);
  pinMode(pinoled4, OUTPUT);
  Serial.begin(9600);
  s.attach(SERVO);
  s.write(0);
}

void loop() {

  SensorLuz();
  SensorTemperatura();
  rfidVerificar();

}
