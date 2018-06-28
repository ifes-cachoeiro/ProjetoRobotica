#include <IRremote.h>
#include <Servo.h>

Servo s; // Variável Servo
int pos; // Posição Servo
#define SERVO 6 // Porta Digital 6 PWM

int RECV_PIN = 5;  
float armazenavalor;  
int pinoledvermelho = 5;  
int pinoledverde = 7;  
  
IRrecv irrecv(RECV_PIN);  
decode_results results;  

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
