/*
   Cores:
   Branco -> padrão (150)
   Vermelho -> para por 5 segundos e depois anda 2 segundos
   Verde -> velocidade máxima (255)
   Azul -> velocidade mínima (50)
   Preto -> encerra a corrida
*/

#define S0 7
#define S1 6
#define S2 3
#define S3 4
#define sensorOut 5
bool stringComplete = false;
String inputString = "";

int azul = 0;
int branco = 0;
int vermelho = 0;
int verde = 0;
int preto = 0;

int frequency = 0;
int cont = 0;

//Motor_A
int IN1 = 7;
int IN2 = 8;
int velocidadeA = 9;

//Motor_B
int IN3 = 10;
int IN4 = 11;
int velocidadeB = 12;

//Variavel auxiliar
int velocidade = 0;

void calibraSensor() {
  char inChar = 'T';
  inputString = "";

  while (inChar != 'E') {
    inChar = 'T';
    stringComplete = false;

    Serial.println("Digite a Cor a ser Lida: A=Red, B=Blue, C=Green, D=White, E=Finalizar");

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

    switch (inChar) {
      case 'A':
        Serial.println("Lendo Red");
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        // Reading the output frequency
        frequency = pulseIn(sensorOut, LOW);
        vermelho = frequency + 5;
        Serial.println(vermelho);
        break;
      case 'B':
        Serial.println("Lendo Blue");
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        // Reading the output frequency
        frequency = pulseIn(sensorOut, LOW);
        azul = frequency + 5;
        Serial.println(azul);
        break;
      case 'C':
        Serial.println("Lendo Green");
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        // Reading the output frequency
        frequency = pulseIn(sensorOut, LOW);
        verde = frequency + 5;
        Serial.println(verde);
        break;
      case 'D':
        Serial.println("Lendo White");
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        // Reading the output frequency
        frequency = pulseIn(sensorOut, LOW);
        branco = frequency + 5;
        Serial.println(branco);
        break;
      case 'E':
        Serial.println("Saindo");
        break;
    }

  }

}

void ligarM(int vel) {

    //Sentido 2
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    //Sentido 2
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(velocidadeA, vel);
    analogWrite(velocidadeB, vel);

    delay(500);

}

//Inicializa Pinos
void setup() {

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  Serial.begin(9600);

  //Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(velocidadeA, OUTPUT);
  pinMode(velocidadeB, OUTPUT);

  calibraSensor();

}

void loop() {

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  Serial.println(frequency);

  if (frequency <= branco) {
    Serial.println("Branco");
    ligarM(200);
  } else if (frequency <= azul) {
    Serial.println("Blue");
    ligarM(150);
  } else if (frequency <= vermelho) {
    Serial.println("Red");
    ligarM(0);
    delay(4500);
    ligarM(200);
  } else if (frequency <= verde) {
    Serial.println("Green");
    ligarM(255);
  } else {
    Serial.println("Black");
    ligarM(0);
  }

}
