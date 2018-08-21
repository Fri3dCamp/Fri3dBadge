#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>
#include <Fri3dMatrix.h>

Fri3dMatrix matrix = Fri3dMatrix();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();

//                            do      do#     re      re#     mi      fa      fa#     sol     sol#    la      la#     si
//                            0       1       2       3       4       5       6       7       8       9       10      11
//                            12      13      14      15      16      17      18      19      20      21      22      23
//                            24      25      26      27      28      29      30      31      32      33      34      35
String notenames [36] = {    "C2",   "C#2",  "D2",   "D#2",  "E2",   "F2",   "F#2",  "G2",   "G#2",  "A2",   "A#2",  "B2",
                             "C3",   "C#3",  "D3",   "D#3",  "E3",   "F3",   "F#3",  "G3",   "G#3",  "A3",   "A#3",  "B3",
                             "C4",   "C#4",  "D4",   "D#4",  "E4",   "F4",   "F#4",  "G4",   "G#4",  "A4",   "A#4",  "B4" };
float frequencies [ 36 ] = { 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
                             261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
                             523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77 }; 

// Broeder Jacob
const int number_of_notes1 = 38;
int notes_sequence1 [ number_of_notes1 ] = { 12, 14, 16, 12, 12, 14, 16, 12,
                                             16, 17, 19, 16, 17, 19,
                                             19, 21, 19, 17, 16, 12, 19, 21, 19, 17, 16, 12,
                                             12, 7, 12, 12, 7, 12 };
float notes_duration1 [ number_of_notes1 ] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                               1.0, 1.0, 2.0, 1.0, 1.0, 2.0,
                                               0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0,
                                               1.0, 1.0, 2.0, 1.0, 1.0, 2.0 };
String s1 = "WE LOVED FRI3D CAMP 2018!";

// Happy Birthday
const int number_of_notes2 = 25;
int notes_sequence2 [ number_of_notes2 ] = { 14, 14, 16, 14, 19, 17,
                                             14, 14, 16, 14, 21, 19,
                                             14, 14, 24, 23, 19, 17, 16,
                                             23, 23, 21, 19, 21, 19 };
float notes_duration2 [ number_of_notes2 ] = { 0.75, 0.25, 1.0, 1.0, 1.0, 2.0,
                                               0.75, 0.25, 1.0, 1.0, 1.0, 2.0,
                                               0.75, 0.25, 1.0, 1.0, 1.0, 1.0, 2.0,
                                               0.75, 0.25, 1.0, 1.0, 1.0, 2.0 };
String s2 = "HAPPY BIRTHDAY BENNY!";

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
    matrix.drawString( 0, notenames[note] );
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
