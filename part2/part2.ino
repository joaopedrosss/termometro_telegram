#include "CTBot.h"
#include "max6675.h" 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 


int ktcSO = 12; //  GPIO12
int ktcCS = 13; // GPIO13
int ktcCLK = 14; // GPIO14
MAX6675 ktc(ktcCLK, ktcCS, ktcSO); 


LiquidCrystal_I2C lcd(0x3F, 16, 2); //definir o endereço do periferico
  
void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(6, 1);
  lcd.print("*C");
  lcd.setCursor(0, 1);

  Serial.begin(9600); 
  delay(500); 
}

void loop(){
   Serial.print("Temperatura: "); 
   Serial.print(ktc.readCelsius()); 
   Serial.println("*C");

   lcd.print(ktc.readCelsius());
  
   delay(500); 
}
