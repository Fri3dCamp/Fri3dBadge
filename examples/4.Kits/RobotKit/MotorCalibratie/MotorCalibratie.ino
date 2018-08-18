#include <Fri3dMatrix.h>
#include <Fri3dServo.h>
#include <Fri3dButtons.h>
#include <Preferences.h>


// Servo Wiring
// 0: left ankle
// 1: right ankle
// 2: left hip
// 3: right hip

#define MODE_SELECT_SERVO   0
#define MODE_SET_MIN   1
#define MODE_SET_MAX   2
#define MODE_PERSIST   3
#define MODE_SUMMARY   4

#define STEP   25

#define SERVO_PIN 32
#define MIN_PULSE_WIDTH       850     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2700     // the longest pulse sent to a servo 

Fri3dServo servo = Fri3dServo();
Fri3dMatrix matrix = Fri3dMatrix();

int servo_pins[4] = {
  32, 25, 26, 27
};

Preferences preferences;

unsigned int min_pulse_width = MIN_PULSE_WIDTH;
unsigned int max_pulse_width = MAX_PULSE_WIDTH;

const char* SERVO_MIN[] = {"s0_min", "s1_min", "s2_min", "s3_min"};
const char* SERVO_MAX[] = {"s0_max", "s1_max", "s2_max", "s3_max"};

Fri3dButtons buttons = Fri3dButtons();

int mode = 0;
bool modeChanged = false;

bool save = false;

int currentServo = 0;
int btn_0_state = 0;
int btn_1_state = 0;
int btn_boot_state = 0;


void setup() {
  preferences.begin("servos", false);
  
  Serial.begin(115200);

  render();
}

void loop() {
  processButtons();
}

void render() {
  matrix.clear();
  
  for (int i = 0; i <= mode; i++) {
    matrix.setPixel(0, i, 1);
  }

  if (mode == MODE_SELECT_SERVO) {
    matrix.drawString(7, "S" + String(currentServo), 1);
  } else if (mode == MODE_SET_MIN) {
    matrix.drawString(3, "-S" + String(currentServo), 1);
  } else if (mode == MODE_SET_MAX) {
    matrix.drawString(3, "+S" + String(currentServo), 1);
  } else if (mode == MODE_PERSIST) {
    // -- ok
    matrix.setPixel(3, 1, true);
    matrix.setPixel(4, 2, true);
    matrix.setPixel(5, 1, true);
    matrix.setPixel(6, 0, true);
    if (save) {
      for (int i = 0; i < 4; i++)
        matrix.setPixel(3 + i, 4, true);
    }

    // -- cancel
    matrix.setPixel(7, 0, true);
    matrix.setPixel(7, 2, true);
    matrix.setPixel(8, 1, true);
    matrix.setPixel(9, 0, true);
    matrix.setPixel(9, 2, true);
    if (!save) {
      for (int i = 0; i < 4; i++)
        matrix.setPixel(7 + i, 4, true);
    }
  } else if (mode == MODE_SUMMARY) {
    if (save) {
      matrix.setPixel(8, 2, true);
      matrix.setPixel(9, 3, true);
      matrix.setPixel(10, 4, true);
      matrix.setPixel(11, 3, true);
      matrix.setPixel(12, 2, true);
      matrix.setPixel(13, 1, true);
    } else {
      matrix.setPixel(8, 0, true);
      matrix.setPixel(8, 4, true);
      matrix.setPixel(9, 1, true);
      matrix.setPixel(9, 3, true);
      matrix.setPixel(10, 2, true);
      matrix.setPixel(11, 1, true);
      matrix.setPixel(11, 3, true);
      matrix.setPixel(12, 0, true);
      matrix.setPixel(12, 4, true);
    }
  }
}

void processButtons() {
  processButton0();
  processButton1();
  processButtonBoot();
}

void processButton0() {
  int val = buttons.getButton(0);
  if (val == btn_0_state) return;
  btn_0_state = val;
  
  if (!val) return;

  if (mode == MODE_SELECT_SERVO) {    // DOWN
    // -- operates as down
    if (currentServo == 0)
      currentServo = 4;

    currentServo--;

  } else if (mode == MODE_SET_MIN) {
    min_pulse_width -= STEP;
    servo.setBoundaries(min_pulse_width, max_pulse_width);
    Serial.print("min: ");
    Serial.println(min_pulse_width, DEC);
    
  } else if (mode == MODE_SET_MAX) {
    max_pulse_width -= STEP;
    servo.setBoundaries(min_pulse_width, max_pulse_width);
    Serial.print("max: ");
    Serial.println(max_pulse_width, DEC);
    
  } else if (mode == MODE_PERSIST) {  // -- change confirm
    save = !save;
  }

  render();
}

void processButton1() {
  int val = buttons.getButton(1);
  if (val == btn_1_state) return;
  btn_1_state = val;
  
  if (!val) return;

  if (mode == MODE_SELECT_SERVO) {    // UP
    ++currentServo %= 4;
    
  } else if (mode == MODE_SET_MIN) {
    min_pulse_width += STEP;
    servo.setBoundaries(min_pulse_width, max_pulse_width);
    Serial.print("min: ");
    Serial.println(min_pulse_width, DEC);
    
  } else if (mode == MODE_SET_MAX) {
    max_pulse_width += STEP;
    servo.setBoundaries(min_pulse_width, max_pulse_width);
    Serial.print("max: ");
    Serial.println(max_pulse_width, DEC);
    
  } else if (mode == MODE_PERSIST) {  // -- change confirm
    if (save) { save = false; }
    else { save = true; }
  }

  render();
}

void processButtonBoot() {
  int val = buttons.getBootButton();
  if (val == btn_boot_state) return;
  btn_boot_state = val;
  
  if (!val) return;
  
  if (!buttons.getBootButton()) return;

  if (mode == MODE_SELECT_SERVO) {    // NEXT
    min_pulse_width = preferences.getUInt(SERVO_MIN[currentServo], MIN_PULSE_WIDTH);
    max_pulse_width = preferences.getUInt(SERVO_MAX[currentServo], MAX_PULSE_WIDTH);
    
    // -- enable the selected servo
    servo.attach(servo_pins[currentServo], min_pulse_width, max_pulse_width);
    
    // -- go to the minimal postion
    servo.write(0);
   
  } else if (mode == MODE_SET_MIN) {
    // -- go to the maximal postion
    servo.write(180);
   
  } else if (mode == MODE_SET_MAX) {
  } else if (mode == MODE_PERSIST) {
    if (save) {
      preferences.putUInt(SERVO_MIN[currentServo], min_pulse_width);
      preferences.putUInt(SERVO_MAX[currentServo], max_pulse_width);
      Serial.print("saved boundaries [");
      Serial.print(min_pulse_width, DEC);
      Serial.print(" -> ");
      Serial.print(max_pulse_width, DEC);
      Serial.print("] for servo ");
      Serial.println(currentServo, DEC);
    }
    
    mode = MODE_SUMMARY;
    render();
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(1000);

    servo.setBoundaries(MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    save = false;
    servo.detach();
  } 

  ++mode %= 5;

  render();
}

