#include <Fri3dButtons.h>
#include <Arduino.h>

Fri3dButtons::Fri3dButtons() {
  pinMode( BUTTONBOOT_PIN, INPUT_PULLUP );
  pinMode( BUTTON0_PIN, INPUT_PULLUP );
  pinMode( BUTTON1_PIN, INPUT_PULLUP );
  pinMode( TOUCH0_PIN, INPUT );
  pinMode( TOUCH1_PIN, INPUT );
}

bool 
Fri3dButtons::getBootButton() {
  return 1 - digitalRead( BUTTONBOOT_PIN );
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

void 
Fri3dButtons::debounceButton( int button ) {
  if ( (millis() - lastDebounceTime[button]) > 50) {
    int buttonState = getButton( button );
    // the button is on a pull-up pin, so stuff here may seem upside down
    if ( (buttonState == 0) && (state[button] != 0 ) ) {
      state[button] = 0;
      lastDebounceTime[button] = millis();
      if( releasedCallbacks[button] )
        (*(releasedCallbacks[button]))();
    }
    else if ( (buttonState == 1) && (state[button] != 1 ) ) {
      state[button] = 1;
      lastDebounceTime[button] = millis();
      if( pressedCallbacks[button] )
        (*(pressedCallbacks[button]))();
    }
  }
}

int 
Fri3dButtons::getDebouncedState( int button ) {
  return state[button];
}


void 
Fri3dButtons::setPressedCallback( int button, void (*callback)() ) {
  pressedCallbacks[button] = callback;
}

void
Fri3dButtons::setReleasedCallback( int button, void (*callback)() ) {
  releasedCallbacks[button] = callback;
}

void debounceThread( void * parameter ) {
  Fri3dButtons* buttons = (Fri3dButtons*)parameter;
  for (;;) {
    for( int button = 0; button < 2; button++ ) {
      buttons->debounceButton( button );
    }
    delay(1);
  }
}

TaskHandle_t debounceTask;
void Fri3dButtons::startDebounceThread() {
  xTaskCreatePinnedToCore(
    debounceThread,             /* Task function. */
    "debounceThread",           /* name of task. */
    1000,                       /* Stack size of task */
    this,                       /* parameter of the task */
    1,                          /* priority of the task */
    &(debounceTask),            /* Task handle to keep track of created task */
    0);                         /* Core */
}

void Fri3dButtons::stopDebounceThread() {
  vTaskDelete(debounceTask);
}
