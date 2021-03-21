#include "Arduino.h"
#include "BlueShift.h"
#include "Wire.h"

#define BRIGHTNESS_PIN      11
#define WHITE_LED_PIN        5
#define FAR_RED_LED_PIN      6
#define I2C_EXPANDER_ADDR    0x40
#define UP_BUTTON_BIT        0     
#define DOWN_BUTTON_BIT      4
#define ALS_PIN              A0

void BlueShift::init(void){
  Wire.begin();
  pinMode(BRIGHTNESS_PIN, OUTPUT);
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(FAR_RED_LED_PIN, OUTPUT);
  pinMode(ALS_PIN, INPUT);
}

/* Integers from 0 to 10, 0 is off, 10 is full brightness */
void BlueShift::setDisplayBrightness(uint8_t brightness){
   if(brightness <= 10){
    analogWrite(BRIGHTNESS_PIN, brightness*10 + 15);
   }
}

/* Integers from 0 to 255, 0 is off, 255 is full brightness */
void BlueShift::setWhiteLED(uint8_t brightness){
  analogWrite(WHITE_LED_PIN, brightness);
}

/* Integers from 0 to 255, 0 is off, 255 is full brightness */
void BlueShift::setInfraredLED(uint8_t brightness){
  analogWrite(FAR_RED_LED_PIN, brightness);
}

bool BlueShift::upButtonPressed(void){
  Wire.requestFrom(I2C_EXPANDER_ADDR, 1);
  uint8_t readPacket;
  while (Wire.available()) {
    readPacket = Wire.read();
  }
  return !(0x01 & (readPacket >> UP_BUTTON_BIT));
}

bool BlueShift::downButtonPressed(void){
  Wire.requestFrom(I2C_EXPANDER_ADDR, 1);
  uint8_t readPacket;
  while (Wire.available()) {
    readPacket = Wire.read();
  }
  return !(0x01 & (readPacket >> DOWN_BUTTON_BIT));
}

uint16_t BlueShift::getALSValue(void){
	analogRead(ALS_PIN);
}