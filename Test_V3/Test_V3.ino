#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=183,155
AudioSynthWaveformSineModulated sine_fm1;       //xy=377,136
AudioEffectEnvelope      envelope1;      //xy=576,149
AudioOutputAnalog        dac1;           //xy=807,179
AudioConnection          patchCord1(sine1, sine_fm1);
AudioConnection          patchCord2(sine_fm1, envelope1);
AudioConnection          patchCord3(envelope1, dac1);
// GUItool: end automatically generated code

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  sine1.amplitude(1);
  sine_fm1.amplitude(1);
  
  envelope1.delay(0);
  envelope1.sustain(1);

  Serial.begin(9600);

}

void loop() {
    
    
    sine1.frequency(analogRead(1));
    sine_fm1.frequency(analogRead(0));
  
    envelope1.attack(map(analogRead(2),0,1023,0,250));
    envelope1.hold(map(analogRead(3),0,1023,0,250));
    envelope1.decay(map(analogRead(4),0,1023,0,250));
    envelope1.release(map(analogRead(5),0,1023,0,250));

    sine1.phase(0);
    sine_fm1.phase(0);
    envelope1.noteOn();
    delay(250);
    envelope1.noteOff();
    delay(10); 
}






