#include <Fri3dMatrix.h>

// rather advanced demo hacking the LEDs to show grayscales

// uses software PWM while rendering the LEDs, per column or row of the matrices
// we render thousands of frames per second, so we can easily turn them on and off
// this code overloads the Fri3dMatrix class with its own class and renderer

// grayscaling columns and rows together gives rather weird effects as the dutycycles sync diagonally

class GrayscaleMatrix : public Fri3dMatrix {
public:
  int frameCounter;
  // a column will light up every dutyCycleX'th frame
  // e.g., a column with dutyCycleX of 4 renders only every 4th frame
  // first seven left eye, next seven right eye
  int dutyCycleX[ 14 ] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  // a column will light up every dutyCycleXth frame
  // first five left eye, next five right eye
  int dutyCycleY[ 10 ] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
public:
  void render( int delay );
};

// we overload the rennder function of the Fri3dMatrix class
// we show the rows and columns only when their cycle equals this framerate
void
GrayscaleMatrix::render( int delay ) {
  frameCounter++;
  for( int row = 0; row < 5; row++ ) {
    
    // send right eye
    for( int i = 0; i < 7; i++ ) 
      if( ( frameCounter % dutyCycleX[ 13 - i ] ) == 0 ) // here's the grayscale magic
        shiftIntoRegister( 1 - buffer[ row ][ 13 - i ] );
      else
        shiftIntoRegister( 1 );
    for( int i = 0; i < 5; i++ ) {
      if( ( row == i ) && ( ( frameCounter % dutyCycleY[ 5 + i ] ) == 0 ) ) // here's the grayscale magic
        shiftIntoRegister( 1 );
      else
        shiftIntoRegister( 0 );
    }
    
    // send left eye
    for( int i = 0; i < 7; i++ )
      if( ( frameCounter % dutyCycleX[ 6 - i ] ) == 0 ) // here's the grayscale magic
        shiftIntoRegister( 1 - buffer[ row ][ 6 - i ] );
      else
        shiftIntoRegister( 1 );
    for( int i = 0; i < 5; i++ ) {
      if( ( row == i ) && ( ( frameCounter % dutyCycleY[ i ] ) == 0 ) ) // here's the grayscale magic
        shiftIntoRegister( 1 );
      else
        shiftIntoRegister( 0 );
    }
      
    digitalWrite( LATCH_PIN, 0 );
    digitalWrite( LATCH_PIN, 1 );
    
    vTaskDelay( delay );
  }
}

GrayscaleMatrix matrix = GrayscaleMatrix();

void setup() {
  Serial.begin(9600);
  matrix.stopRenderThread(); // we'll run our own renderer
}

// we'll have a vertical and horizontal line bouncing up and down at these locations
int x = 0;
int dx = 1;
int y = 0;
int dy = 1;

void loop() {

  // we can draw whatever we want here! we'll draw some basic eyes
  matrix.clear( 1 );
  matrix.setPixel( 0, 0, 0 );
  matrix.setPixel( 6, 0, 0 );
  matrix.setPixel( 0, 4, 0 );
  matrix.setPixel( 6, 4, 0 );
  matrix.setPixel( 3, 2, 0 );
  matrix.setPixel( 7, 0, 0 );
  matrix.setPixel( 13, 0, 0 );
  matrix.setPixel( 7, 4, 0 );
  matrix.setPixel( 13, 4, 0 );
  matrix.setPixel( 10, 2, 0 );

  // fading columns on left eye
  // we'll increase the dutycycle of all columns to darken them
  for( int column = 0; column < 7; column++ ) {
    matrix.dutyCycleX[ column ] = matrix.dutyCycleX[ column ]*1.5+0.5;
  }
  // we'll set our current column in x to full brightness
  matrix.dutyCycleX[ x ] = 1;

  // fading rows on right eye
  // we'll increase the dutycycle of all rows to darken them
  for( int row = 0; row < 5; row++ ) {
    matrix.dutyCycleY[ 5 + row ] = matrix.dutyCycleY[ 5 + row ]*1.5+0.5;
  }
  // we'll set our current column in y to full brightness
  matrix.dutyCycleY[ 5 + y ] = 1;

  // bounce around x and y
  x += dx;
  if( x == 0 ) dx = -dx;
  if( x == 6 ) dx = -dx;
  y += dy;
  if( y == 0 ) dy = -dy;
  if( y == 4 ) dy = -dy;

  // render 1000 frames of this view before updating the loop
  for( int i = 0; i < 800; i++ ) 
    matrix.render( 0 );
}