#include "arduino.hpp"

using namespace arduino;

static const auto LightDetectorPin = digital_pin::d2;
static const auto LedPin = digital_pin::d13;

void setup() {
  set_pin_mode(LightDetectorPin, io_mode::input);
  set_pin_mode(LedPin, io_mode::output);
  write(LedPin, state::low);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto lightDetectorValue = read(LightDetectorPin);  
  Serial.println(lightDetectorValue);
  write(LedPin, lightDetectorValue);
  
  delay(500);
}
