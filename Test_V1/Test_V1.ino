/** Simple FM Synt
 * 
 * Keypad: sine_fm1 freq
 * Pot1  : sine1 freq
 * 
 * Pot2 - 6: parameter Filter
 */


#include <Keypad.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>


int filterCoeffs[5];

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;            
AudioSynthWaveformSineModulated sine_fm1;  
AudioEffectEnvelope      envelope1;     
AudioFilterBiquad        biquad1;         
AudioOutputAnalog        dac1;         

AudioConnection          patchCord1(sine1, sine_fm1);
AudioConnection          patchCord2(sine_fm1, envelope1);
AudioConnection          patchCord3(envelope1, dac1);
//AudioConnection          patchCord4(biquad1, dac1);
// GUItool: end automatically generated code


const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads

char hexaKeys[ROWS][COLS] = {
  {
    'A','B','C'          }
  ,
  {
    'D','E','F'          }
  ,
  {
    'G','H','I'          }
  ,
  {
    'J','K','L'          }
};

byte rowPins[ROWS] = { 
  5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 
  8, 7, 6}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  sine1.amplitude(1);
  sine1.frequency(440);
  sine_fm1.amplitude(1);
  
  envelope1.delay(0);
  envelope1.attack(0);
  envelope1.hold(500);
  envelope1.decay(500);
  envelope1.sustain(1);
  envelope1.release(500);

  Serial.begin(9600);

  customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad

  playNote(220);
  delay(750);
  envelope1.noteOff();
}

void loop() {
  char key = customKeypad.getKey();
  sine1.frequency(analogRead(0)/5);
  for(int i= 0; i < 5;i++)
  {
    filterCoeffs[i] = analogRead(i+1)/5;
  }
  //biquad1.setCoefficients(2,filterCoeffs);  
}

void keypadEvent(KeypadEvent key){
  switch (customKeypad.getState()){
  Serial.print("key: ");
  Serial.println(key);
  case PRESSED:
    switch (key) {

    case 'A':
      playNote(262);
      break;
    case 'B':
      playNote(277);
      break;
    case 'C':
      playNote(294);
      break;
    case 'D':
      playNote(311);    
      break;
    case 'E':
      playNote(330);
      break;
    case 'F':
      playNote(350);
      break;
    case 'G':
      playNote(370);
      break;
    case 'H':
      playNote(392);
      break;
    case 'I':
      playNote(415);
      break;
    case 'J':
      playNote(440);
      break;
    case 'K':
      playNote(466);
      break;
    case 'L':
      playNote(494);

      break;                
    default:
      // do something
      break;
    }
    break;

  case RELEASED:
    envelope1.noteOff();
    break;

  case HOLD:
    break;
  }
}

void playNote(int f1)
{
  sine_fm1.frequency(f1);
  sine1.phase(0);
  sine_fm1.phase(0);
  envelope1.noteOn();
  Serial.println(f1);
  }







