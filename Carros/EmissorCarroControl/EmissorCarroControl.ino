#include <IRremote.h>

IRsend irsend;

//O LED IR deve estar conectado ao pino 3 do Arduino PWM.

int qtdSend = 3;

void setup() {
  Serial.begin(9600);
}

void emitirSinal(int opcao) {

  if (opcao == 1) {

    Serial.println("PARAR");

    for (int i = 0; i < qtdSend; i++) {
      irsend.sendSony(0x1, 32);
      delay(40);
    }

  } else if (opcao == 2) {

    Serial.println("FRENTE");

    for (int i = 0; i < qtdSend; i++) {
      irsend.sendSony(0x2, 32);
      delay(40);
    }

  } else if (opcao == 3) {

    Serial.println("TRAZ");

    for (int i = 0; i < qtdSend; i++) {
      irsend.sendSony(0x3, 32);
      delay(40);
    }

  } else if (opcao == 4) {

    Serial.println("ESQUERDA");

    for (int i = 0; i < qtdSend; i++) {
      irsend.sendSony(0x4, 32);
      delay(40);
    }

  } else if (opcao == 5) {

    Serial.println("DIREITA");

    for (int i = 0; i < qtdSend; i++) {
      irsend.sendSony(0x5, 32);
      delay(40);
    }

  }

}

void loop() {

  int opcao;

  if (Serial.available() > 0) {
    opcao = Serial.parseInt();
    Serial.println(opcao);
    emitirSinal(opcao);
  }

}
