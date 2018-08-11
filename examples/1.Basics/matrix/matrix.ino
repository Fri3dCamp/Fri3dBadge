#include <Fri3dMatrix.h>

Fri3dMatrix matrix = Fri3dMatrix();

void setup() {
}

void loop() {
  matrix.setPixel( rand() % 14, rand() % 5, rand() % 2 );
  delay(10);
}
