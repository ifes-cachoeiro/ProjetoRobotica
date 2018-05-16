#define S0 6
#define S1 7
#define S2 3
#define S3 4
#define sensorOut 5
bool stringComplete = false;
String inputString = "";

int azul=0;
int branco=0;
int vermelho=0;
int verde=0;
int preto=0;

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

void calibraSensor(){
    char inChar = 'T';    
    inputString = "";

  while(inChar != 'E'){
  inChar = 'T';
  stringComplete = false;
  
  Serial.println("Digite a Cor a ser Lida: 1=Red,2=Blue,3=Green,4=White");

  while (!stringComplete) {
    while (Serial.available()) {
      inChar = (char)Serial.read();
      Serial.println(inChar);

      inputString += inChar;
      if (inChar != ' ') {
        stringComplete = true;
        break;
      }
    }
  }

     Serial.println("Teste");

    switch(inChar){
      case 'A':
      Serial.println("Lendo Red");
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      vermelho = frequency+10;
      Serial.println(vermelho);

      break;
      case 'B':
      Serial.println("Lendo Blue");
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      azul = frequency+10;
      break;
      case 'C':
      Serial.println("Lendo Green");
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      verde = frequency+10;
      break;      
      case 'D':
      Serial.println("Lendo White");
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      branco = frequency+10;
      break;
      case 'E':
      Serial.println("Saindo");
      break;
      }

  }
 
}

//Inicializa Pinos
void setup(){

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  Serial.begin(9600);
  
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

  calibraSensor();
  
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

   if(frequency <= branco){
      Serial.println("Branco");
    }else if(frequency <= azul){
       Serial.println("Blue");
      }else if(frequency <= vermelho){
         Serial.println("Red");
      }else if(frequency <= verde){
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
