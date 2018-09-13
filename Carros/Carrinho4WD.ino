//motor_A
int IN1 = 8 ;
int IN2 = 9 ;
int velocidadeA = 2;

//motor_B
int IN3 = 10 ;
int IN4 = 11 ;
int velocidadeB = 3;

//variavel auxiliar
int velocidade = 0;

//Inicializa Pinos
void setup(){
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
}

void loop(){

/*Exemplo de velocidades no motor A*/

//Sentido 2
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);

//Sentido 2
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGHr);

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
