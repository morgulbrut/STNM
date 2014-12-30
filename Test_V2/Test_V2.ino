/** Simple FM Synt
 * 
 * Keypad: sine_fm1 freq
 * Pot1  : sine1 freq
 * 
 * Pot2 - 6: parameter Filter
 */



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
AudioConnection          patchCord3(envelope1, biquad1);
AudioConnection          patchCord4(biquad1, dac1);
// GUItool: end automatically generated code


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


  playNote(220);
  delay(750);
  envelope1.noteOff();
}

void loop() {
    playNote(262);
    delay(250);
    envelope1.noteOff();
    delay(10);
    playNote(311);
    delay(250);
    envelope1.noteOff();
    delay(10);
}


void playNote(int f1)
{
  sine_fm1.frequency(f1);
  sine1.phase(0);
  sine_fm1.phase(0);
  envelope1.noteOn();
  Serial.println(f1);
  }







