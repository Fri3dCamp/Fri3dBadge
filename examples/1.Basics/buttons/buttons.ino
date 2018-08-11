#include <Fri3dButtons.h>

Fri3dButtons buttons = Fri3dButtons();

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print( buttons.getButton( 0 ) );
  Serial.print( "\t" );
  Serial.print( buttons.getButton( 1 ) );
  Serial.print( "\t" );

  // touch both ground and the touchpads
  
  Serial.print( buttons.getTouchpad( 0 ) );
  Serial.print( "\t" );
  Serial.print( buttons.getTouchpad( 1 ));
  Serial.println();
  delay(100);
}