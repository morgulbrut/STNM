#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=188,141
AudioSynthWaveformDc     dc1;            //xy=369,198
AudioSynthWaveformDc     dc2;            //xy=369,261
AudioSynthWaveformSineModulated sine_fm1;       //xy=377,136
AudioFilterStateVariable filter1;        //xy=672,144
AudioFilterStateVariable filter2;        //xy=846,144
AudioEffectEnvelope      envelope1;      //xy=1015,138
AudioOutputAnalog        dac1;           //xy=1229,145

AudioConnection          patchCord1(sine1, sine_fm1);
AudioConnection          patchCord2(dc1, 0, filter1, 1);
AudioConnection          patchCord3(dc2, 0, filter2, 1);
AudioConnection          patchCord4(sine_fm1, 0, filter1, 0);
AudioConnection          patchCord5(filter1, 0, filter2, 0);
AudioConnection          patchCord6(filter2, 2, envelope1, 0);
AudioConnection          patchCord7(envelope1, dac1);
// GUItool: end automatically generated code


uint16_t freqs[128] = {8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 21, 22, 23, 24, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 5920, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
  
  sine1.amplitude(1);
  sine_fm1.amplitude(1);
  
  envelope1.delay(0);
  envelope1.sustain(1);

  envelope1.attack(0);
  envelope1.hold(50);
  envelope1.decay(100);
  envelope1.release(90);
  
  // low pass
  filter1.resonance(0.7);
  filter1.octaveControl(7);
  filter1.frequency(0);

  filter2.resonance(0.7);
  filter2.octaveControl(7);
  filter2.frequency(1);


  dc1.amplitude(0);
  dc2.amplitude(1);
  
  sine1.frequency(440);
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  usbMIDI.setHandleControlChange(OnControlChange);
  
  OnNoteOn(1,62,99);
  delay(500);
  OnNoteOff(1,62,99); 
}

void loop() {
    
    sine1.frequency(analogRead(0));
    
    usbMIDI.read();
 
}

void OnNoteOn (byte channel, byte note, byte velocity) {
      sine_fm1.frequency(freqs[note]);
      sine1.phase(0);
      sine_fm1.phase(0);
      envelope1.noteOn();
}

void OnNoteOff(byte channel, byte note, byte velocity) {
      envelope1.noteOff();
}




void OnControlChange(byte channel, byte control, byte value) {
// This is for MIDI CC signals.  The CC number itself can be
// reassigned by changing the first set of case numbers.  (The
// second just routes the proper channels.)
    if(control == 1)   sine1.frequency(freqs[value]);
    if(control == 72)  envelope1.release(value*2);
    if(control == 73)  envelope1.attack(value*2);    
 }


