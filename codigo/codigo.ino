/*
Termostato de Celcius
Author:
João
Brazil - 2021 
*/

#include "CTBot.h"//robo
#include "max6675.h" //sensor
#include <Wire.h>  //interface i2c
#include <LiquidCrystal_I2C.h>//lcd

CTBot myBot;
String ssid  = "ondas";
String pass  = "12345678";
<<<<<<< HEAD:codigo/codigo.ino
String token = "";  //ID DO BOT
=======
String token = ""; 

int ktcSO = 12; //  GPIO12
int ktcCS = 13; // GPIO13
int ktcCLK = 14; // GPIO14
MAX6675 ktc(ktcCLK, ktcCS, ktcSO); 

LiquidCrystal_I2C lcd(0x27, 16, 2); //definir o endereço do periferico
  
void setup(){
  lcd.init();
  lcd.backlight();
  

  Serial.begin(115200); 
   

  Serial.println("Inicializando bot Telegram...");
  myBot.wifiConnect(ssid, pass); //conectar wifi
  myBot.setTelegramToken(token); //localizar bot
  delay(500);

  if (myBot.testConnection()){
    Serial.println("nConexao Ok!");
  }else{
    Serial.println("nFalha na conexao!");
  }


}

void loop(){
  TBMessage msg; //armazena a mensagem recebida

  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(6, 1);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  float cels = ktc.readCelsius();


  Serial.println("Temperatura: "); 
  Serial.print(ktc.readCelsius()); 
  Serial.println("*C");

  lcd.print(cels);

  String medida = "";
  medida.concat(cels);  

  if (myBot.getNewMessage(msg)){
    if (msg.text.equalsIgnoreCase("TEMPERATURA,CELCIUS")){
      myBot.sendMessage(msg.sender.id, medida );
    } else{
      String ola;
      ola = (String)"Ola," + msg.sender.username + (String)"! Meu nome é Celcius. Peça-me com 'Temperatura,Celcius' e lhe direi a temperatura. ";
      myBot.sendMessage(msg.sender.id, ola);
    }
  }
  

   delay(500); 
} 
