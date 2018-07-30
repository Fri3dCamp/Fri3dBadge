#include "button.h"
#include "Fri3dButtons.h"

Fri3dButtons fri3dButtons = Fri3dButtons();

Button::Button( int button ) {
  this->button = button;
  lastDebounceTime = 0;
  debounceDelay = 50;
  state = 0;
}

ButtonState 
Button::check() {
  if ( (millis() - lastDebounceTime) > debounceDelay) {
    int buttonState = fri3dButtons.getButton( button );
    // the button is on a pull-up pin, so stuff here may seem upside down
    if ( (buttonState == 0) && (state == 1 ) ) {
      state = 0;
      lastDebounceTime = millis(); //set the current time
      return BUTTON_PRESSED;
    }
    else if ( (buttonState == 1) && (state == 0 ) ) {
      state = 1;
      lastDebounceTime = millis(); //set the current time
      return BUTTON_RELEASED;
    }
  }
  if( state )
    return BUTTON_HIGH;
  else
    return BUTTON_LOW;
}

int 
Button::getState() {
  return state;
}

