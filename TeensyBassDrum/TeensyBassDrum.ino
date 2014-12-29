/*
 * A simple hardware test which receives audio on the A2 analog pin
 * and sends it to the PWM (pin 3) output and DAC (A14 pin) output.
 *
 * This example code is in the public domain.
 */
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=73,150
AudioSynthWaveform       waveform2;      //xy=127,256
AudioEffectEnvelope      envelope1;      //xy=248,145
AudioEffectEnvelope      envelope2;      //xy=343,241
AudioSynthWaveformSineModulated sine_fm2;       //xy=416,143
AudioEffectMultiply      multiply1;      //xy=541,237
AudioOutputAnalog        dac1;           //xy=703,208
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(waveform2, envelope2);
AudioConnection          patchCord3(envelope1, sine_fm2);
AudioConnection          patchCord4(envelope2, 0, multiply1, 1);
AudioConnection          patchCord5(sine_fm2, 0, multiply1, 0);
AudioConnection          patchCord6(multiply1, dac1);
// GUItool: end automatically generated code





void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  envelope1.attack(0);
  envelope1.decay(90);
  envelope1.release(90);
  
  envelope2.attack(0);
  envelope2.decay(120);
  envelope2.release(120);
  
  sine_fm2.frequency(40);
  sine_fm2.amplitude(1);
  
  
  waveform1.begin(1,60,WAVEFORM_SQUARE);
  waveform2.begin(1,50,WAVEFORM_SINE);

}

void loop() {
  // Do nothing here.  The Audio flows automatically
  AudioNoInterrupts();
  waveform1.phase(0);
  waveform2.phase(0);

  envelope1.noteOn();
  envelope2.noteOn();
  delay(5);
  envelope1.noteOff();
  envelope2.noteOff();
  AudioInterrupts();
  delay(400);
  // When AudioInputAnalog is running, analogRead() must NOT be used.
}


