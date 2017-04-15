#include <SevenSeg.h>
SevenSeg sevseg(11,10,9,8,7,6,5);
#include "DHT.h"

#define DHTPIN 2     
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

const int numOfDigits=2;
int digitPins[numOfDigits]={4,3};

#define tempRefPin A0  
#define humRefPin A1  
#define tempRelePin 12
#define humRelePin 13
#define PAUSADHT 2000

#define dummyTempPin A2  
#define showSwitch A2

// aproximadamente 4 segundos
#define showTime 200 

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

  dht.begin();
  Serial.begin(9600); 
}



void updateDisplay() {
    if (readTempState()) {
        if(changeTimer > 0) { // mostrar tempRefValue
            sevseg.write(tempRefValue);
        } else { // mostrar temp
            sevseg.write(temp);
        }
    } else { // mostrar humedad
        if(changeTimer > 0) { // mostrar humRefValue
            sevseg.write(humRefValue);
        } else { // mostrar hum
            sevseg.write(hum);
        }
    }
  
}


bool readTempState() {
    return (analogRead(showSwitch) > 256);
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
    changeTimer = showTime; 
  }

  if (prevHumRefValue != humRefValue) {
    changeTimer = showTime; 
  }

  prevTempRefValue = tempRefValue;
  prevHumRefValue = humRefValue;
}


void readDHT() {
// dummy for testing
//    temp = map(analogRead(dummyTempPin), 0, 1023, 15, 35);
    
/*    
  if (millis() > dhtDelay + PAUSADHT) {
    dhtDelay = millis();
    hum = (int)dht.readHumidity();
    temp = (int)dht.readTemperature();

  }
*/  
}


void loop() {
  readDHT();
  readRefValues();
  checkInputValues();
 
  updateDisplay();

  if (changeTimer > 0) {
    changeTimer--;
  }
  
}

