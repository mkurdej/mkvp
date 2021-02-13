// ---------------------------------------------------------------------------
// Connect your piezo buzzer (without internal oscillator) or speaker to these pins:
//   Pins  9 & 10 - ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, etc.
//   Pins 11 & 12 - ATmega2560/2561, ATmega1280/1281, Mega
//   Pins 12 & 13 - ATmega1284P, ATmega644
//   Pins 14 & 15 - Teensy 2.0
//   Pins 25 & 26 - Teensy++ 2.0
// Be sure to include an inline 100 ohm resistor on one pin as you normally do when connecting a piezo or speaker.
// ---------------------------------------------------------------------------

#include <toneAC.h>

#define PLAY_ALL_FREQUENCIES 1
#define PLAY_ALL_VOLUMES 0

// Melody liberated from the toneMelody Arduino example sketch by Tom Igoe.
int melody[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

void play() {
#if PLAY_ALL_FREQUENCIES
  for (unsigned long freq = 20; freq <= 20000; freq += 10) {
    Serial.println(freq);
    toneAC(freq); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
    delay(1);
  }
#elif PLAY_ALL_VOLUMES
  for (uint8_t volume = 0; volume <= 10; ++volume) {
    Serial.println(volume);
    toneAC(500, volume);
    delay(500);
  }
#endif

noToneAC();
delay(1000);

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    toneAC(melody[thisNote], 10, noteDuration, true); // Play thisNote at full volume for noteDuration in the background.
    delay(noteDuration * 4 / 3); // Wait while the tone plays in the background, plus another 33% delay between notes.
  }
}

void setup() {
  Serial.begin(9600);

  play();
}

void loop() {
}
