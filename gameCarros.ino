// Projeto 38 -  Jogo dos caminhões com LCD 16X2

// Declarando a biblioteca para comunicação com o LCD.
#include <LiquidCrystal.h> 

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); // Declarando os pinos a serem usados.
const int POTPIN = 1;  // Potenciometro no pino A1 do Arduino

// Precisamos girar todo o potenciometro para o carrinho subir e... 
//descer no visor do LCD.
const int MAXPOT = 1024; 

// Declara o pino digital 10 para acionar o Speaker.
const int SPEAKERPIN = 10;  

// Um pino analogico que não esta conectado a nada.
const int RANDSEEDPIN = 0; 

// Inicia devagar e a cada milisegundos vai aumetando a velocidade...
const int MINSTEPDURATION = 150; 

// Até chegar ao máximo de sua velocidade.
const int MAXSTEPDURATION = 300; 
const int NGLYPHS = 6;
byte glyphs[NGLYPHS][8] = {  // Iremos criar os carros e caminhões...

  // Imagem carro para cima.
  { B00000,
    B01110,
    B11111,
    B01010,
    B00000,
    B00000,
    B00000,
    B00000}

  // Imagem carro para baixo.
  ,{B00000,
    B00000,
    B00000,
    B00000,
    B01110,
    B11111,
    B01010,
    B00000}

  // Imagem do caminhão para cima.
  ,{B00000,
    B11110,
    B11111,
    B01010,
    B00000,
    B00000,
    B00000,
    B00000}

  // Imagem do caminhão para baixo.
  ,{B00000,
    B00000,
    B00000,
    B00000,
    B11110,
    B11111,
    B01010,
    B00000}

  // Imagem de batida para cima.
  ,{B10101,
    B01110,
    B01110,
    B10101,
    B00000,
    B00000,
    B00000,
    B00000}

  // Imagem de batida para baixo.
  ,{B00000,
    B00000,
    B00000,
    B10101,
    B01110,
    B01110,
    B10101,
    B00000}

};

const int NCARPOSITIONS = 4;

const char BLANK=32;

char car2glyphs[NCARPOSITIONS][2] = {

  {1,BLANK},{2,BLANK},{BLANK,1},{BLANK,2}

};

char truck2glyphs[NCARPOSITIONS][2] = {

  {3,BLANK},{4,BLANK},{BLANK,3},{BLANK,4}

};

char crash2glyphs[NCARPOSITIONS][2] = {

  {5,BLANK},{6,BLANK},{BLANK,5},{BLANK,6}

};

const int ROADLEN = 15; // Largura do LCD (sem contar nosso carro).

int road[ROADLEN]; // Posição dos outros carros.

char line_buff[2+ROADLEN]; 

int road_index;

int car_pos;

// Off-the-grid posição significa coluna vazia, então MAXROADPOS

 // Determina a probabilidade de um carro numa coluna

 // Por exemplo 3 * NCARPOSITIONS dá p = 1/3

const int MAXROADPOS = 3*NCARPOSITIONS;

int step_duration;

int crash; // Verdadeiro se haver colisão.

unsigned int crashtime;

const int CRASHSOUNDDURATION = 250;



const char *INTRO1="OlhePARAfrente";

const char *INTRO2="Tenha cuidado";

const int INTRODELAY = 2000; // Introdução com duração de dois segundos.

void setup()

{

  crash = crashtime = road_index = 0;

  step_duration = MAXSTEPDURATION;

  line_buff[1+ROADLEN] = '\0';

  randomSeed(analogRead(RANDSEEDPIN));

  for (int i=0; i<NGLYPHS; i++) {

    lcd.createChar(i+1,glyphs[i]);

  }

  for (int i=0; i<ROADLEN; i++) {

    road[i]=-1;

  }

  pinMode(SPEAKERPIN,OUTPUT);  // Define pino 10 com de saída.

  analogWrite(SPEAKERPIN,0); // Para estar no lado seguro.

  lcd.begin(16,2);  // Inicia o LCD de 16X2.

  getSteeringWheel();

  drawRoad();

  lcd.setCursor(1,0); // Na primeira coluna e linha 0...

  lcd.print(INTRO1);  // Imprima "CaminhoeAfrente".

  lcd.setCursor(1,1); // Na primeira coluna linha 1...

  lcd.print(INTRO2); // Imprima "Tenha cuidado".

  delay(INTRODELAY); // Aguarda 2 segundos antes de começar o jogo.

}

void loop() {

  unsigned long now = millis()-INTRODELAY;

  if (!crash) {

    getSteeringWheel();

    crash = (car_pos==road[road_index]);

  }

  if (crash) {

    if (!crashtime) {

      crashtime=now;

      drawRoad();

      lcd.setCursor(2,0); // Na coluna 2 lina 0...

      lcd.print("Grave colisao!!"); // Imprima "Grave colisão!!".

      lcd.setCursor(2,1);

      lcd.print(now/1000);

      lcd.print(" segundos.");

    }

    if ((now-crashtime)<CRASHSOUNDDURATION) {

      analogWrite(SPEAKERPIN,random(255)); 

    } 

    else {

      analogWrite(SPEAKERPIN,0); // Havendo colisão ouvimos um som... 
	  //pelo Speaker...   

    }

    delay(10); // De 10 milisegundos.

  } 

  else {

    int prev_pos = road[(road_index-1)%ROADLEN];

    int this_pos = random(MAXROADPOS);

    while (abs(this_pos-prev_pos)<2) { 

      this_pos = random(MAXROADPOS);

    }

    road[road_index] = this_pos;

    road_index = (road_index+1)%ROADLEN;

    drawRoad();

    delay(step_duration); // Delay de 300 milisegundos.
    
    if (step_duration>MINSTEPDURATION) {

      step_duration--; 

    }

  }

}

void getSteeringWheel() {

  car_pos = map(analogRead(POTPIN),0,1024,0,NCARPOSITIONS);

}void drawRoad() {

  for (int i=0; i<2; i++) {

    if (crash) {

      line_buff[0]=crash2glyphs[car_pos][i];

    } 

     else {

      line_buff[0]=car2glyphs[car_pos][i];

    }

  for (int j=0; j<ROADLEN; j++) {

  int pos = road[(j+road_index)%ROADLEN];

  line_buff[j+1]= pos>=0&&pos>NCARPOSITIONS?truck2glyphs[pos][i]:BLANK;

    }

    lcd.setCursor(0,i);

    lcd.print(line_buff);

  }

}
