#include <Fri3dMatrix.h>

Fri3dMatrix matrix = Fri3dMatrix();
String s = "FRI3D CAMP 2018";
int counter = -15;

void setup() {
}

void loop() {
  counter++;
  if( counter > (int)( s.length() + 4 ) * 4 )
    counter = -15;
  matrix.clear();
  for( int i = 0; i < s.length(); i++ ) {
    matrix.drawCharacter( i * 4 - counter, s[ i ] );
  }
  delay(100);
}
