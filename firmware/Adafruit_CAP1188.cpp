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

#include "Adafruit_CAP1188.h"

// byte mySPCR, SPCRback;
byte _i2caddr;
char _resetpin;
bool _i2c;

Adafruit_CAP1188::Adafruit_CAP1188(char resetpin) {
  // I2C
  _resetpin = resetpin;
  _i2c = true;
}

// Adafruit_CAP1188::Adafruit_CAP1188(char cspin, char resetpin) {
  //Hardware SPI
  // _cs = cspin;
  // _resetpin = resetpin;
  // _clk = -1;
  // _i2c = false;
// }

// Adafruit_CAP1188::Adafruit_CAP1188(char clkpin, char misopin, 
				   // char mosipin,char cspin, 
				   // char resetpin) {
  //Software SPI
  // _cs = cspin;
  // _resetpin = resetpin;
  // _clk = clkpin;
  // _miso = misopin;
  // _mosi = mosipin;
  // _i2c = false;
// }

boolean Adafruit_CAP1188::begin(byte i2caddr) {
  if (_i2c) {
    Wire.begin();
    
    _i2caddr = i2caddr;
  } 
  // else if (_clk == -1) {
    //Hardware SPI
    // digitalWrite(_cs, HIGH);
    // SPCRback = SPCR;
    // SPI.begin();
    // SPI.setClockDivider(SPI_CLOCK_DIV8);
    // SPI.setDataMode(SPI_MODE0);
    // mySPCR = SPCR;
    // SPCR = SPCRback;
  // } else {
    //Sofware SPI
    // pinMode(_clk, OUTPUT);
    // pinMode(_mosi, OUTPUT);
    // pinMode(_cs, OUTPUT);
    // digitalWrite(_cs, HIGH);
    // digitalWrite(_clk, HIGH);
  // }

  if (_resetpin != -1) {
    pinMode(_resetpin, OUTPUT);
    digitalWrite(_resetpin, LOW);
    delay(100);
    digitalWrite(_resetpin, HIGH);
    delay(100);
    digitalWrite(_resetpin, LOW);
    delay(100);
  }

  readRegister(CAP1188_PRODID);
  
  // Useful debugging info
  
  Serial.print("Product ID: 0x");
  Serial.println(readRegister(CAP1188_PRODID), HEX);
  Serial.print("Manuf. ID: 0x");
  Serial.println(readRegister(CAP1188_MANUID), HEX);
  Serial.print("Revision: 0x");
  Serial.println(readRegister(CAP1188_REV), HEX);
  

  if ( (readRegister(CAP1188_PRODID) != 0x50) ||
       (readRegister(CAP1188_MANUID) != 0x5D) ||
       (readRegister(CAP1188_REV) != 0x83)) {
    return false;
  }
  // allow multiple touches
  writeRegister(CAP1188_MTBLK, 0); 
  // Have LEDs follow touches
  writeRegister(CAP1188_LEDLINK, 0xFF);
  // speed up a bit
  writeRegister(CAP1188_STANDBYCFG, 0x30);
  return true;
}

byte  Adafruit_CAP1188::touched(void) {
  byte t = readRegister(CAP1188_SENINPUTSTATUS);
  if (t) {
    writeRegister(CAP1188_MAIN, readRegister(CAP1188_MAIN) & ~CAP1188_MAIN_INT);
  }
  return t;
}

void Adafruit_CAP1188::LEDpolarity(byte x) {
  writeRegister(CAP1188_LEDPOL, x);
}

/*********************************************************************/

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static byte i2cread(void) {
  // #if ARDUINO >= 100
  return Wire.read();
  // #else
  // return Wire.receive();
  // #endif
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(byte x) {
  // #if ARDUINO >= 100
  Wire.write((byte)x);
  // #else
  // Wire.send(x);
  // #endif
}

/**************************************************************************/
/*!
    @brief  Reads 8-bits from the specified register
*/
/**************************************************************************/
// byte Adafruit_CAP1188::spixfer(byte data) {
  // if (_clk == -1) {
   //Serial.println("Hardware SPI");
    // return SPI.transfer(data);
  // } else {
   //Serial.println("Software SPI");
    // byte reply = 0;
    // for (int i=7; i>=0; i--) {
      // reply <<= 1;
      // digitalWrite(_clk, LOW);
      // digitalWrite(_mosi, data & (1<<i));
      // digitalWrite(_clk, HIGH);
      // if (digitalRead(_miso)) 
	// reply |= 1;
    // }
    // return reply;
  // }
// }

byte Adafruit_CAP1188::readRegister(byte reg) {
  if (_i2c) {
    Wire.beginTransmission(_i2caddr);
    i2cwrite(reg);
    Wire.endTransmission();
    Wire.requestFrom(_i2caddr, 1);
    return (i2cread());
  } 
  // else {
    // if (_clk == -1) {
      // SPCRback = SPCR;
      // SPCR = mySPCR;
    // }
    // digitalWrite(_cs, LOW);
    //set address
    // spixfer(0x7D);
    // spixfer(reg);
    // digitalWrite(_cs, HIGH);
    // digitalWrite(_cs, LOW);
    // spixfer(0x7F);
    // byte reply = spixfer(0); 
    // digitalWrite(_cs, HIGH);
    // if (_clk == -1) {
      // SPCR = SPCRback;
    // }
    // return reply;
  // }  
  else {
	  return 0;
  }
}


/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void Adafruit_CAP1188::writeRegister(byte reg, byte value) {
  if (_i2c) {
    Wire.beginTransmission(_i2caddr);
    i2cwrite((byte)reg);
    i2cwrite((byte)(value));
    Wire.endTransmission();
  } 
  // else {
    // if (_clk == -1) {
      // SPCRback = SPCR;
      // SPCR = mySPCR;
    // }
    // digitalWrite(_cs, LOW);
    //set address
    // spixfer(0x7D);
    // spixfer(reg);
    // digitalWrite(_cs, HIGH);
    // digitalWrite(_cs, LOW);
    // spixfer(0x7E);
    // spixfer(value);
    // digitalWrite(_cs, HIGH);
    // if (_clk == -1) {
      // SPCR = SPCRback;
    // }
  // }
}
