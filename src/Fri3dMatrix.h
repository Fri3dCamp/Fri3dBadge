// ensure this library description is only included once
#ifndef Fri3dMatrix_h
#define Fri3dMatrix_h

#define LATCH_PIN 15
#define CLOCK_PIN 4
#define DATA_PIN 2
#define ENABLE_PIN 13

// library interface description
class Fri3dMatrix {
public:
  Fri3dMatrix();
  
  void setPixel( int x, int y, int value );
  int getPixel( int x, int y ) const;
  void drawCharacter( int x_offset , char c );
  void clear( int value = 0 );
  
  void render( int delay = 0 ) const;
  void startRenderThread();
  
protected:
  int buffer[5][14];
  void shiftIntoRegister( int b ) const;

};

#endif

