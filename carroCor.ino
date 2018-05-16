#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

int frequency = 0;

//motor_A
int IN1 = 7;
int IN2 = 8;
int velocidadeA = 9;

//motor_B
int IN3 = 10;
int IN4 = 11;
int velocidadeB = 12;

//variavel auxiliar
int velocidade = 0;

//Inicializa Pinos
void setup(){

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  //Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(velocidadeA,OUTPUT);
  pinMode(velocidadeB,OUTPUT);

}

void loop(){
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);

   if(frequency <= 21){
      Serial.println("Branco");
    }else if(frequency <= 36){
       Serial.println("Blue");
      }else if(frequency <= 45){
         Serial.println("Red");
      }else if(frequency <= 60){
         Serial.println("Green");
      }else{
         Serial.println("Black");
      }

  /*Exemplo de velocidades no motor A*/

  //Sentido 2
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  //Sentido 2
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  //velocidade de 0 a 255
  while (velocidadeA < 255){
  analogWrite(velocidadeA,velocidade);
  analogWrite(velocidadeB,velocidade);

  velocidade = velocidade + 10;
  delay(50);
}

  //velocidade de 255 a 0
  while (velocidadeA > 0){
  analogWrite(velocidadeA,velocidade);
  analogWrite(velocidadeB,velocidade);

  velocidade = velocidade - 10;
  delay(50);
}
}
