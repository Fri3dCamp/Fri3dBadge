// ensure this library description is only included once
#ifndef Fri3dAccelerometer_h
#define Fri3dAccelerometer_h

#include "Adafruit_ADXL345_U.h"
#include "Adafruit_Sensor.h"

// library interface description
class Fri3dAccelerometer {
protected:
  Adafruit_ADXL345_Unified adxl345;
public:
  Fri3dAccelerometer();
  
  bool getEvent(sensors_event_t *event);

  void displaySensorDetails(void);
  void displayDataRate(void);
  void displayRange(void);
};

#endif
