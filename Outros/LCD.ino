#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 8, 9, 10, 11);

void setup() {

  lcd.begin(16, 2);
  analogWrite(3, 130); //Aqui utilizamos o pino 3 do Arduino para controlar o contraste do display

}



void loop() {

  lcd.autoscroll();
  lcd.setCursor(0, 0);

  lcd.print("Proj de Robotica!!!");

  lcd.setCursor(0, 1);

  lcd.print("IFES");

  delay(1000);
}
