#include "CTBot.h"
#include "max6675.h" 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

CTBot myBot;
String ssid  = "NOME_DA_REDE_WIFI";
String pass  = "SENHA_WIFI";
String token = "5057650735:AAHJrq_3x9jXQhxjN9T2xrEmHJIlpSaWnAY"; 

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

  Serial.print("Temperatura: "); 
  Serial.print(ktc.readCelsius()); 
  Serial.println("*C");

  float cels = ktc.readCelsius();
  lcd.print(cels);

  String medida = "";
  medida.concat(cels);  

  if (myBot.getNewMessage(msg)){
    if (msg.text.equalsIgnoreCase("TEMPERATURA,CELCIUS")){
      myBot.sendMessage(msg.sender.id, medida );
    } else{
      String ola;
      ola = (String)"Ola, " + msg.sender.username + (String)"! Meu nome é Celcius. Peça-me com 'Temperatura,Celcius' e lhe direi a temperatura. ";
      myBot.sendMessage(msg.sender.id, ola);
    }
  }
  

   delay(500); 
} 