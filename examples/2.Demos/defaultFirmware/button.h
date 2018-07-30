#include <Arduino.h>

enum ButtonState { BUTTON_LOW, BUTTON_HIGH, BUTTON_PRESSED, BUTTON_RELEASED };

class Button {
private:
  int button;
  
  int state;
  long lastDebounceTime;  // the last time the output pin was toggled
  long debounceDelay;    // the debounce time; increase if the output flickers
public:
  
  Button( int button );
  ButtonState check();
  int getState();
};

