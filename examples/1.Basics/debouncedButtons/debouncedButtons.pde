// this examples shows debouncing of buttons which allows for callbacks when buttons are pressed/released

#include <Fri3dButtons.h>

Fri3dButtons buttons = Fri3dButtons();

void button0pressed() {
  Serial.println( "button 0 was pressed" );
}

void button0released() {
  Serial.println( "button 0 was released" );
}

void button1pressed() {
  Serial.println( "button 1 was pressed" );
}

void button1released() {
  Serial.println( "button 1 was released" );
}

void setup() {
  Serial.begin(9600);
  buttons.setPressedCallback( 0, button0pressed );
  buttons.setPressedCallback( 1, button1pressed );
  buttons.setReleasedCallback( 0, button0released );
  buttons.setReleasedCallback( 1, button1released );
  buttons.startDebounceThread();
}

void loop() {
  // no main code required
  delay(1000);
}
