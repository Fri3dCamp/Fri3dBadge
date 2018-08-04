// ensure this library description is only included once
#ifndef Fri3dButtons_h
#define Fri3dButtons_h

#define BUTTONBOOT_PIN 0
#define BUTTON0_PIN 36
#define BUTTON1_PIN 39
#define TOUCH0_PIN 12
#define TOUCH1_PIN 14

// library interface description
class Fri3dButtons {
public:
  Fri3dButtons();
  bool getBootButton();
  bool getButton( int button );
  int getTouchpad( int touchpad );
};

#endif

