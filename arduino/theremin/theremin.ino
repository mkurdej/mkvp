#include "clamp.hpp"

#include <NewPing.h>
#include <toneAC.h>

// Buzzer: Pins  9 & 10 - ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, etc.

#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarVolume(/*trigger=*/12, /*echo=*/11, MAX_DISTANCE);
NewPing sonarFrequency(/*trigger=*/3, /*echo=*/2, MAX_DISTANCE);

int volumeDistance, frequencyDistance;
int volume, frequency;
static const int pingDelayMs = 100;
static const int noteDurationMs = 500;
static const int minFrequency = 20;
static const int maxFrequency = 1000;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  static_assert(pingDelayMs >= 29, "29ms should be the shortest delay between pings.");
  delay(pingDelayMs);

  volumeDistance = sonarVolume.ping_cm();
  frequencyDistance = sonarFrequency.ping_cm();
  //Serial.println(volumeDistance);
  //Serial.println(frequencyDistance);
  volume = map(volumeDistance, /*from*/ 3, MAX_DISTANCE / 2, /*to*/ 0, 10);
  volume = constrain(volume, 0, 10);
  frequency = map(frequencyDistance, /*from*/ 3, MAX_DISTANCE, /*to*/ maxFrequency, minFrequency);
  frequency = constrain(frequency, minFrequency, maxFrequency);
  Serial.println(frequency);
  //Serial.println(volume);

  if (volumeDistance && frequencyDistance) {
    // [3-MAX_DISTANCE] -> [l, h]
    toneAC(frequency, volume, noteDurationMs, /*background=*/true);
  } else {
    noToneAC();
  }
}

