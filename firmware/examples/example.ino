/***************************************************
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to 
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries. 
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
//#include <Wire.h>
//#include <SPI.h>
#include <TreeLamp/Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  4

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
//#define CAP1188_MOSI  11
//#define CAP1188_MISO  12
//#define CAP1188_CLK  13

volatile byte interrupt = 0;

// Publish debugging info to Dashboard TBA.
int debug = 0;

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
 Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println("CAP1188 test!");
  pinMode(3,INPUT);
  // Raise SPI slave select (SS) pins
  // Communication begins when you drop the individual select signals to LOW
  digitalWrite(10,HIGH);
 

  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    Particle.publish("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
  Particle.publish("CAP1188 found!");
  pinMode(3, INPUT);
  // Turn off multitouch so only one button pressed at a time
  cap.writeRegister(0x2A, 0x80);  // 0x2A default 0x80 use 0x41  — Set multiple touches back to off
  cap.writeRegister(0x41, 0x39);  // 0x41 default 0x39 use 0x41  — Set "speed up" setting back to off
  cap.writeRegister(0x72, 0x00);  // 0x72 default 0x00  — Sets LED links back to off (default)
  cap.writeRegister(0x44, 0x41);  // 0x44 default 0x40 use 0x41  — Set interrupt on press but not release
  cap.writeRegister(0x28, 0x00);  // 0x28 default 0xFF use 0x00  — Turn off interrupt repeat on button hold
  //EIFR = 1; // clear flag for interrupt 1
  attachInterrupt(1, routine_Interrupt_CAP1188, FALLING);
}

void loop() {
 
  // Serial.println(digitalRead(3));
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    // return;
  }
 
  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      Serial.print("C"); Serial.print(i+1); Serial.print("\t");
    }
  }
  Serial.println();
  delay(50);
  Serial.print("Interrupt: ");  Serial.println(interrupt);
  Particle.publish("Interrupt: ",Serial.println(interrupt);)
}

void routine_Interrupt_CAP1188()  {
  ++interrupt;
}
