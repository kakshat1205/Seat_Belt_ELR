#include <LiquidCrystal.h>
float x,y,z;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(4,1);
  lcd.print("Accelerometer values....");
  delay(2000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(1,0);
  //lcd.print("ROBUINO");
  delay(300);
  lcd.setCursor(5,1);
  //lcd.print("By");
  delay(300);
  lcd.setCursor(6,2);
  //lcd.print("yahya rhiba");
  delay(300);
  lcd.setCursor(3,3);
  //lcd.print("project");
  delay(3000);
  lcd.clear();
  delay(1000);
  //lcd.print("->YR");
  lcd.setCursor(14,0);
  lcd.print("21<-");
}

void loop() {
  x = ((analogRead(A0)*2.0)/1024.0)-1;  
  y = ((analogRead(A1)*2.0)/1024.0)-1;
  z = ((analogRead(A2)*2.0)/1024.0)-1; 
  lcd.setCursor(6,1);
  lcd.print("gX = ");
  lcd.print(x);
  lcd.setCursor(6,2);
  lcd.print("gY = ");
  lcd.print(y);
  lcd.setCursor(6,3);
  lcd.print("Z = ");
  lcd.print(z);
  delay(30);
}
