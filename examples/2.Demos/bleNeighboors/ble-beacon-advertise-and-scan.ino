/*
CREDITS:
* Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
* Ported to Arduino ESP32 by Evandro Copercini
* Hacked by zoobab and okso during HaxoGreen 2018
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include <Fri3dMatrix.h>

uint64_t chipid; 

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "111fc111-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "11154111-36e1-4688-b7f5-ea07361b26a8"

int scanTime = 30; //In seconds

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

Fri3dMatrix matrix = Fri3dMatrix();

void displayNumbers( int left , int right ) {
  matrix.clear();
  if( left < 10 )
    matrix.drawString( 4, String( left ) );
  else
    matrix.drawString( 0, String( left ) );
  if( right < 10 )
    matrix.drawString( 11, String( right ) );
  else
    matrix.drawString( 7, String( right ) );
}

void setup() {
  Serial.begin(115200);
  Serial.println("===== Setup the Beacon... =====");

  chipid = chipid=ESP.getEfuseMac();

  String fried = "fried";
  String friedmac = fried + String((uint32_t)chipid);

  Serial.println("My beacon name is: " + friedmac);

  BLEDevice::init(friedmac.c_str());
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

void loop() {
  Serial.println("===== Scanning... =====");
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  
  Serial.println("===== Number of badges: ===== ");
  int counter=0;
  for (int i=0; i<foundDevices.getCount(); i++) {
     String blename = foundDevices.getDevice(i).getName().c_str();
     if ( blename.indexOf("fried") == 0 ){
//         Serial.println(blename);
         counter++;
     }
  }
//  Serial.println("\nTotal:\n");
  Serial.println(counter);
  displayNumbers(0, counter);
}
