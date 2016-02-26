/***************************************************
  Library code written by Limor Fried/Ladyada for Adafruit Industries.
  Example code written by Mauricio Sanchez Duque/sheva29
  
 ****************************************************/


// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_CAP1188.h"

//For SDA in Photon use pin D0
//For SCK in Photon use pin D1
// VIN works with both 3.3V and 5V

Adafruit_CAP1188 cap = Adafruit_CAP1188();

void setup() {

  Serial.begin(19200);
  cap.begin();

  //we set our level of sensitivity
  //we pass values from 1 to 7
  cap.setSensitivity(6);

}

void loop() {

  //cap.touchedAnalog(1) will call second electrode analog values
  for (byte i = 0; i < 8; i++){
    int8_t analogValues = cap.touchedAnalog(i);
    Serial.print(i);Serial.print(" : ");Serial.print(analogValues);Serial.print("\t");
  }
  Serial.println();
}
