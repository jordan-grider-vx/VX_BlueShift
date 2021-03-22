#ifndef BlueShift_h
#define BlueShift_h
#include "Arduino.h"

enum button_state_t {
	BUTTON_NO_PRESS,
	BUTTON_SHORT_UP,
	BUTTON_LONG_UP,
	BUTTON_SHORT_DOWN,
	BUTTON_LONG_DOWN,
	BUTTON_BOTH_PRESS
};

class BlueShift
{
public:
	bool init50005(uint16_t);
	button_state_t buttonManager(void);
	void setDisplayBrightness(uint8_t brightness);
	void setWhiteLED(uint8_t brightness);
	void setInfraredLED(uint8_t brightness);
	bool upButtonPressed(void);	
	bool downButtonPressed(void);
    uint16_t getALSValue(void);
private:
};

#endif