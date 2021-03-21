#ifndef BlueShift_h
#define BlueShift_h
#include "Arduino.h"


class BlueShift
{
public:
	void init(void);
	void setDisplayBrightness(uint8_t brightness);
	void setWhiteLED(uint8_t brightness);
	void setInfraredLED(uint8_t brightness);
	bool upButtonPressed(void);	
	bool downButtonPressed(void);
    int getALSValue(void);
private:
};

#endif