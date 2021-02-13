static const int LedPin = 10;
// static const int LedPort = 0b00100000;

int msDelay = 3000;
float factor = 0.75;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin, OUTPUT);
  Serial.begin(9600);
}

void blinkLed(int pin, int delayMillis) {
  digitalWrite(pin, HIGH);
  // PORTB = PORTB | LedPort;
  delay(delayMillis);
  digitalWrite(pin, LOW);
  // PORTB = PORTB & (~LedPort);
  delay(delayMillis);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(msDelay);
  //Serial.println(factor);

  if (msDelay < 5) factor = 1.5;
  if (msDelay > 3000) factor = 0.75;

  msDelay *= factor;

  blinkLed(LedPin, msDelay);
}
