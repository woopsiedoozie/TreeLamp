/*************************************************** 
  This is a library for the CAP1188 8-Channel Capacitive Sensor

  Designed specifically to work with the CAP1188 breakout from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// #if (ARDUINO >= 100)
 // #include "Arduino.h"
// #else
 // #include "WProgram.h"
// #endif
// #include <Wire.h>
// #include <SPI.h>
#include "application.h"

// The default I2C address
#define CAP1188_I2CADDR 0x29

// Some registers we use
#define CAP1188_SENINPUTSTATUS 0x3
#define CAP1188_MTBLK 0x2A
#define CAP1188_LEDLINK 0x72
#define CAP1188_PRODID 0xFD
#define CAP1188_MANUID 0xFE
#define CAP1188_STANDBYCFG 0x41
#define CAP1188_REV 0xFF
#define CAP1188_MAIN 0x00
#define CAP1188_MAIN_INT 0x01
#define CAP1188_LEDPOL 0x73


class Adafruit_CAP1188 {
 public:
  //Software SPI
  // Adafruit_CAP1188(char clkpin, char misopin, 
		   // char mosipin,char cspin, 
		   // char resetpin);
  //Hardware SPI
  // Adafruit_CAP1188(char cspin, char resetpin);
  // Hardware I2C
  Adafruit_CAP1188(char resetpin = -1);

  boolean begin(byte i2caddr = CAP1188_I2CADDR);
  byte readRegister(byte reg);
  void writeRegister(byte reg, byte value);
  byte touched(void);
  void LEDpolarity(byte x);

 private:
  // byte spixfer(byte x);
  boolean _i2c;
  char _i2caddr;
  // char _i2caddr, _resetpin, _cs, _clk, _mosi, _miso;
};
