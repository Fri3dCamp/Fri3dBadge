// ensure this library description is only included once
#ifndef Fri3dButtons_h
#define Fri3dButtons_h

#define BUTTON0_PIN 36
#define BUTTON1_PIN 39
#define TOUCH0_PIN 12
#define TOUCH1_PIN 14

// library interface description
class Fri3dButtons {
public:
  Fri3dButtons();
  bool getButton( int button );
  int getTouchpad( int touchpad );

// below is all the stuff needed for automated debouncing with callbacks
  void debounceButton( int button );
private:
  int state[2];
  int lastDebounceTime[2];
  void (*pressedCallbacks[2])();
  void (*releasedCallbacks[2])();
public:
  void setPressedCallback( int button, void (*callback)() );
  void setReleasedCallback( int button, void (*callback)() );
  void startDebounceThread();
  void stopDebounceThread();
  
};

#endif

