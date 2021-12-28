#include "max6675.h" 

int ktcSO = 12; //  GPIO12
int ktcCS = 13; // GPIO13
int ktcCLK = 14; // GPIO14
 

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); 
  
void setup(){
  Serial.begin(9600); 
  delay(500); 
}

void loop(){
   Serial.print("Temperatura: "); 
   Serial.print(ktc.readCelsius());
   Serial.println("*C"); 
   delay(500); 
}