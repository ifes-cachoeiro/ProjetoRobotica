#include <IRremote.h>
#include <Servo.h>

int ldrPin = 0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
int sensorPin = 5; //the analog pin the TMP36's Vout (sense) pin is connected to

Servo s; // Variável Servo
int pos; // Posição Servo
#define SERVO 6 // Porta Digital 6 PWM

int RECV_PIN = 5;
float armazenavalor;
int pinoledvermelho = 5;
int pinoledverde = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;
void SensorLuz() {

  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  //se o valor lido for maior que 500, liga o led
  if (ldrValor >= 800) digitalWrite(ledPin, HIGH);
  // senão, apaga o led
  else digitalWrite(ledPin, LOW);
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

void ControleRemoto(){
  if (irrecv.decode(&results))
  {
    Serial.print("Valor lido : ");
    Serial.println(results.value, HEX);
    armazenavalor = (results.value);
    if (armazenavalor == 0xFFFFFFFF) //Verifica se a tecla 1 foi acionada
    {
      ServoMotor();
      digitalWrite(pinoledverde, HIGH);  //Acende o led vermelho
    }
    if (armazenavalor == 0xFD30CF) //Verifica se a tecla 2 foi acionada
    {
      digitalWrite(pinoledverde, LOW); //Apaga o led vermelho
    }
    if (armazenavalor == 0xFF10EF) //Verifica se a tecla 4 foi acionada
    {
      digitalWrite(pinoledverde, HIGH); //Acende o led verde
    }
    if (armazenavalor == 0xFF38C7) //Verifica se a tecla 5 foi acionada
    {
      digitalWrite(pinoledverde, HIGH); //Apaga o led verde
    }
    if (armazenavalor == 0xFF52AD) //Verifica se a tecla 9 foi acionada
    {
      digitalWrite(pinoledverde, HIGH); //Apaga todos os leds
      digitalWrite(pinoledverde, HIGH);
    }
    irrecv.resume(); //Le o próximo valor
  }
  }

void setup()
{
  pinMode(pinoledvermelho, OUTPUT);
  pinMode(pinoledverde, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicializa o receptor IR
  s.attach(SERVO);
  s.write(0);
}

void loop()
{

  ControleRemoto();
  SensorLuz();
  SensorTemperatura();
}
