#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define tempRefPin A0  
#define humRefPin A1  
#define tempRelePin 6
#define humRelePin 7
#define PAUSADHT 2000

int tempRefValue = 0; 
int humRefValue = 0; 
int tempRefLowValue = 0; 
int humRefLowValue = 0; 


int hum = 70;
int temp = 23;
unsigned long dhtDelay;

void setup() {
  lcd.begin(16, 2);
  dhtDelay = millis();
}

// 0123456789ABCDFG
// T:23 R: 28
// H:70 R: 80

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
  if (millis() > dhtDelay + PAUSADHT) {
    dhtDelay = millis();
    // leer con el dht  
      // leo hum
      // leo temp
  }

  tempRefValue = map(analogRead(tempRefPin), 0, 1023, 15, 35);
  humRefValue = map(analogRead(humRefPin), 0, 1023, 30, 100);
  
  updateLcd();

  
}

