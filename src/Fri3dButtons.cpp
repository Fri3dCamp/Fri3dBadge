#include <Fri3dButtons.h>
#include <Arduino.h>


Fri3dButtons::Fri3dButtons() {
  pinMode( BUTTON0_PIN, INPUT_PULLUP );
  pinMode( BUTTON1_PIN, INPUT_PULLUP );
  pinMode( TOUCH0_PIN, INPUT );
  pinMode( TOUCH1_PIN, INPUT );
}

bool 
Fri3dButtons::getButton( int button ) {
  if( button == 0 )
    return 1 - digitalRead( BUTTON0_PIN );
  else if( button == 1 )
    return 1 - digitalRead( BUTTON1_PIN );
  else
    return false;
}

int
Fri3dButtons::getTouchpad( int touchpad ) {
  if( touchpad == 0 )
    return analogRead( TOUCH0_PIN );
  else if( touchpad == 1 )
    return analogRead( TOUCH1_PIN );
  else
    return -1;
}
