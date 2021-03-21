#include <Wire.h>
#include <BlueShift.h>

BlueShift blueshift;
int display_brightness = 4;                //Brightness scale 0-10, 0 is off, 10 is maximum brightness
bool als_controlled_brightness = false;    //Brightness for display automatically controlled by the ambient light sensor input

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("BlueShift Example");
 
  blueshift.init();
  blueshift.setDisplayBrightness(display_brightness);
}

void loop() {
  buttonManager();
  
  
  delay(10);
}

void ALSManager(void) {
  
}

void buttonManager(void) {
  bool upButtonState = blueshift.upButtonPressed();
  bool downButtonState = blueshift.downButtonPressed();
  static bool upButtonLastState;
  static bool downButtonLastState;
  unsigned long upHoldTime;
  unsigned long downHoldTime;

  if (upButtonState && !upButtonLastState) {
    upHoldTime = millis();
  }

  if (downButtonState && !downButtonLastState) {
    downHoldTime = millis();
    Serial.println("Down Button Press.");
  }

  if (!upButtonState && upButtonLastState && !downButtonState) {
    upHoldTime = millis() - upHoldTime;
    if (upHoldTime > 50) {
      if (upHoldTime < 1000) {
        if(!als_controlled_brightness);
        turnUpBrightness();
        Serial.println("Up button short press");
      } else {
        toggleWhiteLED();
        Serial.println("Up button long press");
      }
    }
  }

  if (!downButtonState && downButtonLastState && !upButtonState) {
    downHoldTime = millis() - downHoldTime;
    if (downHoldTime > 50) {
      if (downHoldTime < 1000) {
        if(!als_controlled_brightness);
        turnDownBrightness();
        Serial.println("Down button short press");
      } else {
        toggleIrLED();
        Serial.println("Down button long press");
      }
    }
  }

  if (!downButtonState || !upButtonState && downButtonLastState && upButtonLastState){
    als_controlled_brightness = !als_controlled_brightness;
    Serial.print("ALS Controlling Brightness: ");
    Serial.println(als_controlled_brightness);    
  }

  upButtonLastState = upButtonState;
  downButtonLastState = downButtonState;
}

void turnUpBrightness(void) {
  if (display_brightness < 10)
  {
    display_brightness++;
  }
  Serial.print("Display Brightness: ");
  Serial.println(display_brightness);
  blueshift.setDisplayBrightness(display_brightness);
}

void turnDownBrightness(void) {
  if (display_brightness > 0)
  {
    display_brightness--;
  }
  Serial.print("Display Brightness: ");
  Serial.println(display_brightness);
  blueshift.setDisplayBrightness(display_brightness);
}

void toggleWhiteLED(void) {
  static bool isOn = false;
  if (isOn) {
    blueshift.setWhiteLED(0);
    Serial.println("White LED off");
  } else {
    blueshift.setWhiteLED(100);
    Serial.println("White LED on");
  }
  isOn = !isOn;
}

void toggleIrLED(void) {
  static bool isOn = false;
  if (isOn) {
    blueshift.setInfraredLED(0);
    Serial.println("Infrared LED off");
  } else {
    blueshift.setInfraredLED(100);
    Serial.println("Infrared LED on");
  }
  isOn = !isOn;
}
