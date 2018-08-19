#include <Fri3dLegs.h>
#include <Fri3dMatrix.h>
#include <Fri3dAccelerometer.h>
#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "111fc111-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "11154111-36e1-4688-b7f5-ea07361b26a8"

Fri3dAccelerometer accel = Fri3dAccelerometer();
Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();
Fri3dLegs legs;

uint64_t chipid; 
bool attached = false;
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;

      buzzer.setVolume(255);
      buzzer.setFrequency( 700 );
      delay( 300 );
      buzzer.setVolume(0);
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;

      buzzer.setVolume(255);
      buzzer.setFrequency( 300 );
      delay( 300 );
      buzzer.setVolume(0);
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
          Serial.print(rxValue[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void toggleAttached() {
  if (attached) { 
    legs.detach();
    attached = false;
  } else {
    legs.attach();
    attached = true;
  }
}

void setup() {
  chipid = ESP.getEfuseMac();

  Serial.begin(115200);
  legs.attach();
  attached = true;
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

  buttons.setReleasedCallback( 0, toggleAttached );
  buttons.startDebounceThread();

  startBLEBeacon();

//  buttons.setReleasedCallback( 0, nextState );
//  buttons.setReleasedCallback( 1, nextState );
//  buttons.startDebounceThread();
}

void loop() {
  renderFoxEyes();
  readSerial(); 
}

void readSerial() {
  while (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
      
    if (in.startsWith("LL")) {
      legs.leanToLeft(4);
    } else if (in.startsWith("LR")) {
      legs.leanToRight(4); 
    } else if (in.startsWith("LC")) {
      legs.straight(4);
    } else if (in.startsWith("F")) {
      legs.stepForward();
    } else if (in.startsWith("B")) {
      legs.stepBackward();  
    } else if (in.startsWith("TL")) {
      legs.turnLeft();
    } else if (in.startsWith("TR")) {
      legs.turnRight();  
    } else if (in.startsWith("HL")) {
      legs.helloLeft();
    } else if (in.startsWith("HR")) {
      legs.helloRight();
    } else if (in.startsWith("R")) {
      legs.reset(); 
    } else if (in.startsWith("D")) {
      legs.detach();
    } else if (in.startsWith("A")) {
      legs.attach();
    } else {
      Serial.println("Unknown command");
    }
  }
}

void startBLEBeacon() {
  Serial.println("===== Setup the Beacon... =====");

  String fri3d = "fri3d";
  String fri3dmac = fri3d + String((uint32_t)chipid);

  Serial.println("My beacon name is: " + fri3dmac);

  BLEDevice::init(fri3dmac.c_str());

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Robot Control");
  pCharacteristic->setCallbacks(new MyCallbacks());
  
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  
  Serial.println("Beacon operational! You should be able to see it on your Beacon scanner, for example on your phone!");
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

