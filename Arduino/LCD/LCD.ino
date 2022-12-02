#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
}

void loop() {
  lcd.setCursor(5, 0);
  lcd.print("HI~^^");
  delay(1000);
  lcd.setCursor(3, 1);
  lcd.print("codingrun");
  delay(1000);
  lcd.clear();
  delay(1000);
}