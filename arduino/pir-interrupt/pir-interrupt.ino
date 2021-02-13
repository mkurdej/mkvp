// Arduino Uno (328-based) can use only digital pins 2 & 3 for interrupts
static const auto LightDetectorPin = 2;
static const auto MotionDetectorPin = 2;

size_t detections = 0;

void onMotionDetection() {
  ++detections;
  //Serial.print("detections: ");
  Serial.println(detections);
}

void setup() {
  pinMode(LightDetectorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(MotionDetectorPin), onMotionDetection, FALLING);
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
