#include "Fri3dBuzzer.h"
#include "Arduino.h"

Fri3dBuzzer::Fri3dBuzzer() {
  ledcSetup( 5, 3000, 8 );
  setVolume( 0 );
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
