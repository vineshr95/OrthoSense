#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
// GUItool: begin automatically generated code
AudioAnalyzeFFT1024    myFFT;
// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=232.0161895751953,102.03934478759766
AudioFilterStateVariable filter1;        //xy=381.01619720458984,139.0393409729004
AudioFilterStateVariable filter2; //xy=510.0161819458008,127.26157188415527
AudioOutputUSB           usb1;           //xy=657.0162696838379,105.03933811187744
AudioConnection          patchCord1(adc1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, filter2, 0);
AudioConnection          patchCord3(filter2, 2, usb1, 0);
AudioConnection          patchCord4(filter2, 2, usb1, 1);
AudioConnection          patchCord5(filter2, 0, myFFT, 0);
// GUItool: end automatically generated code
// GUItool: end automatically generated code
void setup() {                
  AudioMemory(12);
  filter1.frequency(2900);
  filter2.frequency(47);
  myFFT.windowFunction(AudioWindowHanning1024);
}
void loop() {
  float n;
  int i;
  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
    for (i=0; i<40; i++) {
      n = myFFT.read(i);
      if (n >= 0.01) {
        Serial.print(n);
        Serial.print(" ");
      } else {
        Serial.print("  -  "); // don't print "0.00"
      }
    }
    Serial.println();
  }
}
