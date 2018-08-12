#include <Fri3dBuzzer.h>

Fri3dBuzzer buzzer = Fri3dBuzzer();

float notes[ 13 ] = { 659.25,587.33,369.99,415.3 ,554.37,493.88,293.66,329.63,493.88,440,277.18,329.63,440 };
float lengths[ 13 ] = { 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 6 };

void setup() {
  buzzer.setVolume( 255 );
}

void loop() {
  for( int i = 0; i < 13; i++ ) {
    buzzer.setFrequency( notes[i] );
    delay( 120 * lengths[i] );
  }
  buzzer.setVolume(0);
  delay(1000 * ( rand() % 40 ) );
}
