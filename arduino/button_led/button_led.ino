static const int LedPin = 13;
static const int ButtonPin = 2;

int previousButtonState = LOW;
int buttonState = previousButtonState;
int ledState = LOW;

void setup() {
  pinMode(LedPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  Serial.begin(9600);
}

void toggleLed(int ledPin) {
  if (ledState == HIGH) {
    ledState = LOW;
  } else {
    ledState = HIGH;
  }
  digitalWrite(ledPin, ledState);
}

void checkButton(int buttonPin, int ledPin) {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState == previousButtonState) return;
  previousButtonState = buttonState;

  if (buttonState == LOW) return;

  toggleLed(ledPin);
}

void loop() {
  checkButton(ButtonPin, LedPin);
}
