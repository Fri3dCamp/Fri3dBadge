#include <Fri3dMatrix.h>

Fri3dMatrix matrix = Fri3dMatrix();
String s = "FRI3D CAMP 2018";

void setup() {
}

void loop() {
  for( int i = -15; i < (int)( s.length() ) * 4; i++ ) {
    matrix.clear();
    matrix.drawString( -i, s );
    delay(100);
  }
}