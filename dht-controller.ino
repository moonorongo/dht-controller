#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tempRefPin = A0;  
float tempRefValue = 0; 
int humRefPin = A1;  
float humRefValue = 0; 

// faltaria temperatura minima...
// y humedad minima (que seran automaticos, 2 grados menos para temperatura, 10% menos
// para humedad

int tempRelePin = 6;
int humRelePin = 7;

float hum = 70.5;
float temp = 23.5;

void setup() {
  lcd.begin(16, 2);
}

// 0123456789ABCDFG
// T: 23.5  Max: 28
// H: 70.5  Max: 80

void updateLcd() {
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temp);

  lcd.setCursor(8, 0);
  lcd.print(" M: ");
  lcd.print(tempRefValue);
    
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(hum);
  lcd.print(" ");

  lcd.setCursor(8, 1);
  lcd.print(" M: ");
  lcd.print(humRefValue);
  lcd.print(" ");
}

void loop() {
  //delay(2000); // pausa para no saturar el dht
  // esto mejorarlo, si no no voy a poder ver en el display un puto valor
  // maquina de estados
  
  // leo humedad
  // leo temperatura

  // 70 1024
  // 15 0
  //  ((x / 1024) * 55) + 15
  //  ((x / 1024) * 100

// NO ANDAM, PONE 15 Y 0, VER QUE ESTA MAL EN LAS FN
  
  tempRefValue = (((analogRead(tempRefPin) + 1) / 1024) * 55) + 15;
  humRefValue = ((analogRead(humRefPin) + 1) / 1024) * 100;

  // temperatura: que ajuste entre 15-35
  // humedad: de 0 a 100
  
  updateLcd();
}

