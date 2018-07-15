// ensure this library description is only included once
#ifndef Fri3dBuzzer_h
#define Fri3dBuzzer_h

#define BUZZER_PIN 33

// library interface description
class Fri3dBuzzer {
public:
  Fri3dBuzzer();
  void setFrequency( int frequency );
  void setVolume( int volume );
};

#endif