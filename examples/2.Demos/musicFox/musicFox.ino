#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>
#include <Fri3dMatrix.h>

Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();

//                            do      do#     re      re#     mi      fa      fa#     sol     sol#    la      la#     si
// 
String notenames [36] = {    "C2",   "C#2",  "D2",   "D#2",  "E2",   "F2",   "F#2",  "G2",   "G#2",  "A2",   "A#2",  "B2",
                             "C3",   "C#3",  "D3",   "D#3",  "E3",   "F3",   "F#3",  "G3",   "G#3",  "A3",   "A#3",  "B3",
                             "C4",   "C#4",  "D4",   "D#4",  "E4",   "F4",   "F#4",  "G4",   "G#4",  "A4",   "A#4",  "B4" };
float frequencies [ 36 ] = { 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
                             261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
                             523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77 }; 

// Broeder Jacob
int number_of_notes1 = 38;
int notes_sequence1 [ 38 ] = { 13, 15, 17, 13, 13, 15, 17, 13,
                               17, 18, 20, 17, 18, 20,
                               20, 22, 20, 18, 17, 13, 20, 22, 20, 18, 17, 13,
                               13, 8, 13, 13, 8, 13 };
float notes_duration1 [ 38 ] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                 1.0, 1.0, 2.0, 1.0, 1.0, 2.0,
                                 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0,
                                 1.0, 1.0, 2.0, 1.0, 1.0, 2.0 };
String s1 = "We loved Fri3d Camp 2018!";

// Happy Birthday
int number_of_notes2 = 25;
int notes_sequence2 [ 25 ] = { 15, 15, 17, 15, 20, 18,
                               15, 15, 17, 15, 22, 20,
                               15, 15, 25, 24, 20, 18, 17,
                               24, 24, 22, 20, 22, 20 };
float notes_duration2 [ 25 ] = { 0.75, 0.25, 1.0, 1.0, 1.0, 2.0,
                                 0.75, 0.25, 1.0, 1.0, 1.0, 2.0,
                                 0.75, 0.25, 1.0, 1.0, 1.0, 1.0, 2.0,
                                 0.75, 0.25, 1.0, 1.0, 1.0, 2.0 };
String s2 = "Happy Birthday Benny!";

void setColumn ( int column, int number_of_rows, int on_off ) {
  for ( int i = 0; i < number_of_rows; i++ ) {
    matrix.setPixel ( column, i, on_off );
  }
}

void setup() {
  buzzer.setVolume( 0 );
  matrix.clear();
}

void loop() {
  int *notes_sequence;
  float *notes_duration;
  int number_of_notes;
  int note;
  int melody;
  String s;
  while (!buttons.getButton( 0 ) and !buttons.getButton( 1 )) { delay ( 10 ); }
  if (buttons.getButton( 0 )) { 
    melody = 1;
    number_of_notes = number_of_notes1;
    notes_sequence = notes_sequence1;
    notes_duration = notes_duration1;
    s = s1;
  }
  else {
    melody = 2;
    number_of_notes = number_of_notes2;
    notes_sequence = notes_sequence2;
    notes_duration = notes_duration2;
    s = s2;
  }
  for( int i = 0; i < number_of_notes; i++ ) {
    buzzer.setVolume( 255 );
    note = *(notes_sequence + i);
    buzzer.setFrequency( frequencies[note] );
    matrix.clear();
    matrix.drawString( -i, notenames[note] );
    setColumn ( note - 13, 5, 1 ); 
    delay( 500 * *(notes_duration + i) );
    buzzer.setVolume(0);
    matrix.clear(); 
    delay( 10 );
  }

    for( int i = -15; i < (int)( s.length() ) * 4; i++ ) {
    matrix.clear();
    matrix.drawString( -i, s );
    delay( 100 );
  }
}
