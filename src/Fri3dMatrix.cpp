/*
  Fri3dMatrix.h - Fri3dMatrix library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include this library's description file
#include "Fri3dMatrix.h"
#include "Arduino.h"

Fri3dMatrix::Fri3dMatrix() {
  pinMode( LATCH_PIN, OUTPUT );
  digitalWrite( LATCH_PIN, 1 );
  pinMode( CLOCK_PIN, OUTPUT );
  digitalWrite( CLOCK_PIN, 0 );
  pinMode( DATA_PIN, OUTPUT );
  digitalWrite( DATA_PIN, 0 );
  pinMode( ENABLE_PIN, OUTPUT );
  digitalWrite( ENABLE_PIN, 0 );
  
  for( int y = 0; y < 5; y++ )
    for( int x = 0; x < 14; x++ )
      buffer[ y ][ x ] = 0;
}

void Fri3dMatrix::shiftIntoRegister( int b ) const {
  digitalWrite( DATA_PIN, b );
  digitalWrite( CLOCK_PIN, 1 );
  digitalWrite( CLOCK_PIN, 0 );
}

void Fri3dMatrix::setPixel( int x, int y, int value ) {
  buffer[ y ][ x ] = value;
}

int Fri3dMatrix::getPixel( int x, int y ) const {
  return buffer[ y ][ x ];
}

void Fri3dMatrix::render() const {
  for( int row = 0; row < 5; row++ ) {
    
    // send right eye
    for( int i = 0; i < 7; i++ ) {
      shiftIntoRegister( 1 - buffer[ row ][ 13 - i ] );
    }
    for( int i = 0; i < 5; i++ ) {
      if( row == i )
        shiftIntoRegister( 1 );
      else
        shiftIntoRegister( 0 );
    }
    
    // send left eye
    for( int i = 0; i < 7; i++ ) {
      shiftIntoRegister( 1 - buffer[ row ][ 6 - i ] );
    }
    for( int i = 0; i < 5; i++ ) {
      if( row == i )
        shiftIntoRegister( 1 );
      else
        shiftIntoRegister( 0 );
    }
      
    digitalWrite( LATCH_PIN, 0 );
    digitalWrite( LATCH_PIN, 1 );
  }
}