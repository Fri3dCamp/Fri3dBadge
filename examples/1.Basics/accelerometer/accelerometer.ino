#include <Fri3dAccelerometer.h>

Fri3dAccelerometer accel = Fri3dAccelerometer();

void setup() {
  Serial.begin(9600);
  accel.begin();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);

}
