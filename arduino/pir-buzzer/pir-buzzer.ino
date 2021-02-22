constexpr uint8_t buzzer_pin = 2;
constexpr uint8_t pir_pin = 3;
constexpr uint8_t led_pin = 13; // internal LED

#include "pitches.h" //https://www.arduino.cc/en/Tutorial/toneMelody

// Parameters
void setup() {
  // Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  pinMode(led_pin, OUTPUT);
  pinMode(pir_pin, INPUT);
}

void loop() {
  auto pir_state = digitalRead(pir_pin);
  if (pir_state == HIGH) {
    // Detected.
    digitalWrite(led_pin, HIGH);
    Serial.println(F("Detected!"));

    playPassed();
    // playFailed();
  } else {
    digitalWrite(led_pin, LOW);
    Serial.println(F("Not detected!"));
  }
}

void playPassed() {
  ////Play 'ON' Sound
  int melodyOn[] = {NOTE_C5, NOTE_C6, NOTE_D5, NOTE_A6};
  int durationOn = 200;
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    tone(buzzer_pin, melodyOn[thisNote], durationOn);
    delay(200);
  }
}

void playFailed() {
  ////Play 'OFF' Sound
  int melodyOff[] = {NOTE_C3, NOTE_D3};
  int durationOff = 200;
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    tone(buzzer_pin, melodyOff[thisNote], durationOff);
    delay(200);
  }
}
