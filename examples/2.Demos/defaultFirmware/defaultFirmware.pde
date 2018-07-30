// this is the default firmware for the Fri3d Camp badge
// it is used both for testing the badge's hardware and to serve as a default demo of what the badge can do
// if you want to learn how to program the badge, it is recommended to look at the basic examples first

#include "button.h"

#include <Fri3dMatrix.h>
#include <Fri3dAccelerometer.h>
#include <Fri3dBuzzer.h>

Fri3dAccelerometer accel = Fri3dAccelerometer();
Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();

// the Button class supports debouncing
Button button0 = Button( 0 );
Button button1 = Button( 1 );

void setup() {
  Serial.begin(9600);
  buzzer.setVolume( 255 );
  buzzer.setFrequency( 600 );
  delay( 120 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setVolume(0);
}

int frame = 0;
int frame_blink = 40;
void renderFoxEyes() {
  // render eyes based on accelerometer
  sensors_event_t event; 
  accel.getEvent(&event);
  matrix.clear();
  int x = 1 + 5 * ( event.acceleration.y + 12 ) / 24;
  if( frame_blink - 2 > frame ) {
    matrix.setPixel( x    , 0, 1 );
    matrix.setPixel( x + 7, 0, 1 );
    matrix.setPixel( x    , 4, 1 );
    matrix.setPixel( x + 7, 4, 1 );
  }
  if( frame_blink - 1 > frame ) {
    matrix.setPixel( x - 1, 1, 1 );
    matrix.setPixel( x    , 1, 1 );
    matrix.setPixel( x + 1, 1, 1 );
    matrix.setPixel( x + 6, 1, 1 );
    matrix.setPixel( x + 7, 1, 1 );
    matrix.setPixel( x + 8, 1, 1 );
    
    matrix.setPixel( x - 1, 2, 1 );
    matrix.setPixel( x + 1, 2, 1 );
    matrix.setPixel( x + 6, 2, 1 );
    matrix.setPixel( x + 8, 2, 1 );

    matrix.setPixel( x - 1, 3, 1 );
    matrix.setPixel( x    , 3, 1 );
    matrix.setPixel( x + 1, 3, 1 );
    matrix.setPixel( x + 6, 3, 1 );
    matrix.setPixel( x + 7, 3, 1 );
    matrix.setPixel( x + 8, 3, 1 );
  }
  if( frame_blink == frame ) {
    matrix.setPixel( x - 1, 2, 1 );
    matrix.setPixel( x    , 2, 1 );
    matrix.setPixel( x + 1, 2, 1 );
    matrix.setPixel( x + 6, 2, 1 );
    matrix.setPixel( x + 7, 2, 1 );
    matrix.setPixel( x + 8, 2, 1 );
    frame_blink = frame_blink + rand() % 10 + 75;
  }
  frame++;
  delay(50);
}

String s = "FRI3D CAMP 2018";
void renderText() {
  if( frame >= (int)( s.length() ) * 4 )
    frame = -15;
  matrix.clear();
  matrix.drawString( -frame, s );
  delay(100);
  frame++;
}

void renderPixels() {
  if( frame < 70 )
    matrix.setPixel( frame % 14, frame / 14, 1 );
  else
    matrix.setPixel( ( frame - 70 ) % 14, ( frame - 70 ) / 14, 0 );
  frame++;
  if( frame >= 140 ) {
    frame = 0;
  }
  delay(10);
}

enum State { STATE_EYES, STATE_TEXT };
State state = STATE_EYES;

int brightness = HIGH;
void loop() {
  int button0state = button0.check();
  int button1state = button1.check();
  if( button0state == BUTTON_HIGH )
    renderPixels();
  else
    switch(state) {
      case STATE_EYES: 
        renderFoxEyes();
      break;
      case STATE_TEXT: 
        renderText(); 
      break;
    }
  if( ( button0state == BUTTON_RELEASED ) || ( button1state == BUTTON_RELEASED ) ) {
    Serial.println("BOO");
    if( state == STATE_EYES )
      state = STATE_TEXT;
    else if( state == STATE_TEXT )
      state = STATE_EYES;
  }
}
