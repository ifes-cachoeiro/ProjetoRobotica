#include <Servo.h>
#include <math.h>

#define PINO_MOTOR_1 13 // elevador
#define PINO_MOTOR_2 11 // extensor
#define PINO_MOTOR_3 12 // garra
#define PINO_MOTOR_4 10 // rotacao

#define GARRA_FECHADA 122
#define GARRA_ABERTA 150

#define ELEVACAO_MINIMA 0
#define ELEVACAO_MAXIMA 0

#define EXTENSAO_MINIMA 90
#define EXTENSAO_MAXIMA 180

#define ROTACAO_MINIMA 25
#define ROTACAO_MAXIMA 180

#define ANGULO_EXTENSOR_VERTICAL 105
#define ANGULO_ELEVADOR_HORIZONTAL 170
#define ANGULO_ROTACAO_MAX_DIREITA 24

Servo motorElevador;
Servo motorExtensor;
Servo motorGarra;
Servo motorRotacao;

String inputString = "";
boolean stringComplete = false;

int anguloMotorElevador;
int anguloMotorExtensor;
int anguloMotorGarra;
int anguloMotorRotacao;

boolean sentidoRotacao;

void setup() {
  motorElevador.attach(PINO_MOTOR_1);
  motorExtensor.attach(PINO_MOTOR_2);
  motorGarra.attach(PINO_MOTOR_3);
  motorRotacao.attach(PINO_MOTOR_4);
  
  motorElevador.write(120);
  anguloMotorElevador = 120;
  delay(100);
  motorExtensor.write(100);
  anguloMotorExtensor = 100;
  delay(100);
  motorGarra.write(GARRA_FECHADA);
  anguloMotorGarra = GARRA_FECHADA;
  delay(200);
  motorRotacao.write(120);
  anguloMotorRotacao = 120;
  delay(100);

  Serial.begin(9600);
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

// valores entre -180 e +180
double determinaAnguloInclinacaoReta(double x1, double x2, double y1, double y2) {
  double deltaX = x2 - x1;
  double deltaY = y2 - y1;
  double coeficienteAngular = atan(deltaY / deltaX) * 180 / M_PI;
  // verifica quadrante do vetor resultante (deltaX, deltaY) (se for 1º ou 4º, tudo certo, mas se for 2º ou 3º, precisa de ajustes por causa da tangente)
  if (deltaX < 0) {
    if (deltaY > 0) {
      coeficienteAngular = 180 + coeficienteAngular;
    } else {
      coeficienteAngular = coeficienteAngular - 180;
    }
  }
  return coeficienteAngular;
}

boolean determinarAngulosHastes(double xd, double yd, int* anguloExtensor, int* anguloElevador) {
  // inserir o codigo desenvolvido na atividade "Programacao de dispositivo robotico - parte 1"
  // deve ser adaptado (se necessario) para receber parametros xd e yd do tipo double 
  double x1, x2, y1, y2, A1, A2, B_1, B2, C1, C2, a, b, c;
  if (yd != 0) {
    a = 1 + (xd * xd) / (yd * yd);
    b = - (xd * xd + yd * yd) * xd / (yd * yd);
    c = (xd * xd + yd * yd) * (xd * xd + yd * yd) / (4 * yd * yd) - 64;
    x1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    x2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    y1 = sqrt(64 - x1 * x1);
    y2 = sqrt(64 - x2 * x2);
  } else {
    x1 = xd / 2;
    x2 = x1;
    y1 = sqrt(64 - x1 * x1);
    y2 = -sqrt(64 - x1 * x1);
  }
  A1 = determinaAnguloInclinacaoReta(0, x1, 0, y1); // ja convertido para graus (*180/pi)
  A2 = determinaAnguloInclinacaoReta(0, x2, 0, y2);
  B_1 = determinaAnguloInclinacaoReta(x1, xd, y1, yd);
  B2 = determinaAnguloInclinacaoReta(x2, xd, y2, yd);
  C1 = 180 - A1 + B_1;
  C2 = 180 - A2 + B2;
  double A = 0, B = 0, C = 0;
  if (C1 > 170) {
    A = A2;
    B = B2;
  } else {
    A = A1;
    B = B_1;
  }
  *anguloExtensor = (int)A;
  *anguloElevador = (int)B;
}

void calcularAngulos(double xd, double yd, double zd, int* alfa, int* beta, int* delta) {
    if (zd > 0) {
        if (xd == 0) *alfa = 90;
        else if (xd > 0) *alfa = (int) (atan(zd / xd) * 180 / M_PI);
        else *alfa = (int) (atan(zd / (-xd)) * 180 / M_PI);
    } else {
        if (xd >= 0) *alfa = 0;
        else *alfa = 180;
    }
    double x1, x2, y1, y2;
    if (yd != 0) {
        double a = 1 + square(xd) / square(yd);
        double b = - (xd * (square(xd) + square(yd))) / square(yd);
        double c = square((square(xd) + square(yd)) / (2 * yd)) - 64;
        x1 = (-b + sqrt(square(b) - 4 * a * c)) / (2 * a);
        x2 = (-b - sqrt(square(b) - 4 * a * c)) / (2 * a);
        y1 = (-2 * xd * x1 - square(xd) - square(yd)) / (2 * yd);
        y2 = (-2 * xd * x2 - square(xd) - square(yd)) / (2 * yd);
    } else {
        x1 = xd / 2; x2 = x1;
        y1 = sqrt(64 - square(x1) + 2 * xd * x1 - square(xd));
        y2 = sqrt(64 - square(x2) + 2 * xd * x2 - square(xd));
    }
    double beta1, beta2, delta1, delta2, teta1, teta2;
    beta1 = atan(y1 / x1) * 180 / M_PI;
    delta1 = atan((yd - y1) / (xd - x1)) * 180 / M_PI;
    teta1 = 180 - beta1 + delta1;
    beta2 = atan(y2 / x2) * 180 / M_PI;
    delta2 = atan((yd - y2) / (xd - x2)) * 180 / M_PI;
    teta2 = 180 - beta2 + delta2;
    if (teta1 <= 180) {
        *beta = beta1;
        *delta = delta1;
    } else {
        *beta = beta2;
        *delta = delta2;
    }
}


boolean calcularAngulosMotores(double xd, double yd, double zd, int* anguloRotacao, int* anguloExtensor, int* anguloElevador) {
  // inserir codigo desenvolvido na atividade "Programacao de dispositivo robotico - parte 2"
  // deve ser adaptado (se necessario) para receber parametros xd, yd e zd do tipo double 
  double alfa;
  if (xd >= 0)
    alfa = atan(abs(zd) / abs(xd)) * 180 / M_PI;
  else
    alfa = 180 - atan(abs(zd) / abs(xd)) * 180 / M_PI;
  *anguloRotacao = alfa;
  xd = sqrt(xd * xd + zd * zd);
  determinarAngulosHastes(xd, yd, anguloExtensor, anguloElevador);
}

void moverMotorPara(Servo motor, int *anguloAtualMotor, int anguloDestino) {
  int inc = 1;
  if (anguloDestino < *anguloAtualMotor)
    inc = -1;
  for (int i = *anguloAtualMotor; i != anguloDestino; i = i + inc) {
    motor.write(i);
    delay(30);
  }
  *anguloAtualMotor = anguloDestino;
}


void moverExtensorParaAngulo(int angulo) {
  int anguloMotor = ANGULO_EXTENSOR_VERTICAL + 90 - angulo;
  moverMotorPara(motorExtensor, &anguloMotorExtensor, anguloMotor);
}

void moverElevadorParaAngulo(int angulo) {
  int anguloMotor = ANGULO_ELEVADOR_HORIZONTAL + angulo;
  moverMotorPara(motorElevador, &anguloMotorElevador, anguloMotor);
}

void moverRotorParaAngulo(int angulo) {
  int anguloMotor = ANGULO_ROTACAO_MAX_DIREITA + angulo;
  moverMotorPara(motorRotacao, &anguloMotorRotacao, anguloMotor);
}

void moverBaseDaGarraParaPonto3D(double xd, double yd, double zd) {
  int anguloExtensor, anguloElevador, anguloRotacao;
  calcularAngulosMotores(xd, yd, zd, &anguloRotacao, &anguloExtensor, &anguloElevador);
  moverRotorParaAngulo(anguloRotacao);
  moverExtensorParaAngulo(anguloExtensor);
  moverElevadorParaAngulo(anguloElevador);
}

void loop() {
  serialEvent(); //call the function
  if (stringComplete) {
    char opcao = inputString.charAt(0);
    int angulo;
    switch (opcao) {
      case 'e':
        angulo = (inputString.charAt(1) - '0') * 100 + (inputString.charAt(2) - '0') * 10 + (inputString.charAt(3) - '0');
        Serial.print("Elevador: ");
        moverMotorPara(motorElevador, &anguloMotorElevador, angulo);
        break;
      case 'x':
        angulo = (inputString.charAt(1) - '0') * 100 + (inputString.charAt(2) - '0') * 10 + (inputString.charAt(3) - '0');
        Serial.print("Extensor: ");
        moverMotorPara(motorExtensor, &anguloMotorExtensor, angulo);
        break;
      case 'g':
        angulo = (inputString.charAt(1) - '0') * 100 + (inputString.charAt(2) - '0') * 10 + (inputString.charAt(3) - '0');
        Serial.print("Garra: ");
        moverMotorPara(motorGarra, &anguloMotorGarra, angulo);
        break;
      case 'r':
        angulo = (inputString.charAt(1) - '0') * 100 + (inputString.charAt(2) - '0') * 10 + (inputString.charAt(3) - '0');
        Serial.print("Rotacao: ");
        moverMotorPara(motorRotacao, &anguloMotorRotacao, angulo);
        break;
      case 'p': // Exemplo: "p:-82,+40,+50"
        // codigo para obter as coordenadas x, y e z de inputString
        // obter a coordenada x
        int sinalX = inputString.charAt(2) == '-' ? -1 : +1;
        double x = sinalX * ((inputString.charAt(3) - '0') * 10 + (inputString.charAt(4) - '0')) / 10;
        // obter a coordenada y
        int sinalY = inputString.charAt(6) == '-' ? -1 : +1;
        double y = sinalY * ((inputString.charAt(7) - '0') * 10 + (inputString.charAt(8) - '0')) / 10;
        // obter a coordenada z
        int sinalZ = inputString.charAt(10) == '-' ? -1 : +1;
        double z = sinalZ * ((inputString.charAt(11) - '0') * 10 + (inputString.charAt(12) - '0')) / 10;
        // chamar a funcao moverBaseDaGarraParaPonto3D
        moverBaseDaGarraParaPonto3D(x, y, z);
    }
    Serial.println(angulo);
    inputString = "";
    stringComplete = false;
    Serial.flush();
  }
  delay(300);
}

