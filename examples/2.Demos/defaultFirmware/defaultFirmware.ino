// this is the default firmware for the Fri3d Camp badge
// it is used both for testing the badge's hardware and to serve as a default demo of what the badge can do
// if you want to learn how to program the badge, it is recommended to look at the basic examples first

#include <Fri3dMatrix.h>
#include <Fri3dAccelerometer.h>
#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>

Fri3dAccelerometer accel = Fri3dAccelerometer();
Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();

// state machine

enum State { STATE_EYES, STATE_TEXT };
State state = STATE_EYES;

void nextState() {
  switch( state ) {
    case STATE_EYES:
      state = STATE_TEXT;
    break;
    case STATE_TEXT:
      state = STATE_EYES;
    break;
  }
}

// BLE Beacon advertises itself as "fri3d" + its unique ID

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "111fc111-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "11154111-36e1-4688-b7f5-ea07361b26a8"

uint64_t chipid; 

void startBLEBeacon() {
    Serial.println("===== Setup the Beacon... =====");

  chipid = chipid=ESP.getEfuseMac();

  String fri3d = "fri3d";
  String fri3dmac = fri3d + String((uint32_t)chipid);

  Serial.println("My beacon name is: " + fri3dmac);

  BLEDevice::init(fri3dmac.c_str());
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Beacon operational! You should be able to see it on your Beacon scanner, for example on your phone!");
}

// SETUP, ARDUINO STYLIE

void setup() {
  Serial.begin(9600);
  
  accel.begin();
  
  buzzer.setVolume( 255 );
  buzzer.setFrequency( 600 );
  delay( 120 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setVolume(0);
  
  buttons.setReleasedCallback( 0, nextState );
  buttons.setReleasedCallback( 1, nextState );
  buttons.startDebounceThread();

  startBLEBeacon();
}

// RENDER FOX EYES WITH ACCELEROMETER

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
    frame_blink = frame_blink + rand() % 90 + 30;
  }
  frame++;
  if( frame > frame_blink )
    frame_blink = frame + rand() % 90 + 30;
  delay(50);
}

// FONT SCROLLY

String s = "FRI3D CAMP 2018";
void renderText() {
  if( frame >= (int)( s.length() ) * 4 )
    frame = -15;
  matrix.clear();
  matrix.drawString( -frame, s );
  delay(100);
  frame++;
}

// PIXEL TEST

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

// MAIN LOOP

void loop() {
  if( buttons.getDebouncedState(0) )
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
}