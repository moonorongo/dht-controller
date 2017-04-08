#include <SevenSeg.h>
SevenSeg sevseg(11,10,9,8,7,6,5);

const int numOfDigits=2;
int digitPins[numOfDigits]={4,3};

#define tempRefPin A0  
#define humRefPin A1  
#define tempRelePin 12
#define humRelePin 13
#define PAUSADHT 2000

#define dummyTempPin A2  
#define showSwitch A3

int tempRefValue = 0; 
int humRefValue = 0; 
int tempRefLowValue = 0; 
int humRefLowValue = 0; 
int prevTempRefValue = tempRefValue;
int prevHumRefValue = humRefValue;


int hum = 70;
int temp = 23;
int changeTimer = 0;
unsigned long dhtDelay;

void setup() {
  sevseg.setDigitPins(numOfDigits ,digitPins);
  sevseg.setCommonCathode();
  sevseg.write(temp);
  
  dhtDelay = millis();
  pinMode(tempRelePin, OUTPUT);
  pinMode(humRelePin, OUTPUT);
  digitalWrite(tempRelePin, LOW);
  digitalWrite(humRelePin, LOW);
}

void updateDisplay() {
//    if (esta_seleccionado mostrar temperatura) {
        if(changeTimer > 0) { // mostrar tempRefValue
            sevseg.write(tempRefValue);
        } else { // mostrar temp
            sevseg.write(temp);
        }
//    } else { // mostrar humedad
        
//    }
  
}



void checkInputValues() {
    if (temp >= tempRefValue) {
        digitalWrite(tempRelePin, LOW);
    }

    if (temp <= tempRefLowValue) {
        digitalWrite(tempRelePin, HIGH);
    }

    if (hum >= humRefValue) {
        digitalWrite(humRelePin, LOW);
    }

    if (hum <= humRefLowValue) {
        digitalWrite(humRelePin, HIGH);
    }

}

void readRefValues() {
  tempRefValue = map(analogRead(tempRefPin), 0, 1023, 15, 35);
  humRefValue = map(analogRead(humRefPin), 0, 1023, 30, 99);
  tempRefLowValue = tempRefValue - 2; 
  humRefLowValue = humRefValue - 10; 

  if (prevTempRefValue != tempRefValue) {
    changeTimer = 50; 
  }

  if (prevHumRefValue != humRefValue) {
    changeTimer = 50; 
  }

  prevTempRefValue = tempRefValue;
  prevHumRefValue = humRefValue;
}


void readDHT() {
// dummy for testing
    temp = map(analogRead(dummyTempPin), 0, 1023, 15, 35);
    
/*    
  if (millis() > dhtDelay + PAUSADHT) {
    dhtDelay = millis();
    // leer con el dht  
      // leo hum
      // leo temp
  }
*/  
}

/*
showSwitch: implementar que switchee entre 2 estados, para mostrar/editar temperatura/humedad 

*/

void loop() {
  readDHT();
  readRefValues();
  checkInputValues();
 
  updateDisplay();

  if (changeTimer > 0) {
    changeTimer--;
  }
  
}

