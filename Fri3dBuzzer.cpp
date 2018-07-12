#include "Fri3dBuzzer.h"
#include "Arduino.h"

Fri3dBuzzer::Fri3dBuzzer() {
  ledcSetup( 0, 3000, 8 );
  setVolume( 255 );
  ledcAttachPin(33, 0);
}

void 
Fri3dBuzzer::setFrequency( int frequency ) {
  ledcWriteTone( 0, frequency );
}

void 
Fri3dBuzzer::setVolume( int volume ) {
  ledcWrite( 0, volume );
}
