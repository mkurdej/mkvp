static const auto LightDetectorPin = 2;
static const auto LedPin = 13;

void setup() {
  pinMode(LightDetectorPin, INPUT);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto lightDetectorValue = digitalRead(LightDetectorPin);  
  Serial.println(lightDetectorValue);
  digitalWrite(LedPin, lightDetectorValue);
  
  delay(500);
}
