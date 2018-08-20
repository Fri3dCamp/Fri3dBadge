#include <Fri3dLegs.h>
#include <Fri3dMatrix.h>
#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>

Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();
Fri3dLegs legs;

void detach() {
  legs.detach();
}

void setup() {
  Serial.begin(115200);
  legs.attach();
  Serial.println("attached");

  buzzer.setVolume( 255 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setVolume(0);
  delay( 500 );
  buzzer.setVolume( 255 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setFrequency( 700 );
  delay( 120 );
  buzzer.setVolume(0);

//  buttons.setReleasedCallback( 0, detach );
//  buttons.startDebounceThread();
}

void loop() {
  moveLoop(); 
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Verplaats de robot ...
//
////////////////////////////////////////////////////////////////////////////////////////////////

void moveLoop() {
    int strategy = random(5);
  
    switch (strategy) {
      case 0:
        legs.stepForward();
        break;
      case 1:
        legs.stepBackward();
        break;
      case 2:
        legs.turnLeft();
        break;
      case 3:
        legs.turnRight();  
        break;
      case 4:
        legs.helloLeft();
        break;
    }

    delay(1000);
}
