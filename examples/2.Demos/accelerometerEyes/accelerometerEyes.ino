// eyes on the matrix move along with the accelerometer

#include <Fri3dMatrix.h>
#include <Fri3dAccelerometer.h>

Fri3dAccelerometer accel = Fri3dAccelerometer();
Fri3dMatrix matrix = Fri3dMatrix();

void setup() {
  Serial.begin(9600);
}

void loop() {

  if( rand() % 50 == 0 ) {
    
    // blink
    
    matrix.clear( 0 );
    for( int x = 2; x < 13; x++ )
      matrix.setPixel( x, 2, 1 );

  } else {

    // render eyes based on accelerometer

    sensors_event_t event; 
    accel.getEvent(&event);

    matrix.clear( 1 );
    for( int x = 0; x < 15; x++ )
    for( int y = 1; y < 5; y++ )
      matrix.setPixel( x, y, 0 );
  
    int x = 7 * ( event.acceleration.y + 15 ) / 30;
    int y = 5 * ( event.acceleration.z + 15 ) / 30;
    matrix.setPixel( x, y , 1 );
    matrix.setPixel( 7 + x, y , 1 );
    
  }

  delay(80);

}