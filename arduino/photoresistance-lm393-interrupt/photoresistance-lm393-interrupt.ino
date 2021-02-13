static const auto LightDetectorPin = 2;

size_t detections = 0;

void onLightDetection() {
  ++detections;
  Serial.print("detections: ");
  Serial.println(detections);
}

void setup() {
  pinMode(LightDetectorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(LightDetectorPin), onLightDetection, FALLING);
}

void loop() {
#if 0
  auto lightDetectorValue = digitalRead(LightDetectorPin);  
  Serial.println(lightDetectorValue);
  
  Serial.print("detections: ");
  Serial.println(detections);

  delay(500);
#endif
}
