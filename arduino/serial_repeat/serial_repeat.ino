/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#include <string.h>

static const int LedPin = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
}

static const size_t serial_buffer_size = 64;

void parseCommand(const char * command, size_t length) {
  if (0 == strncmp("LED=on", command, min(6, length))) {
    digitalWrite(LedPin, HIGH);
    Serial.println("LED=on");
  } else if (0 == strncmp("LED=off", command, min(6, length))) {
    digitalWrite(LedPin, LOW);
    Serial.println("LED=off");
  } else {
    Serial.print("Unrecognised command: ");
    Serial.println(command);
  }
}

void serialEvent() {
  if (0 == Serial.available()) return;

  char buffer[serial_buffer_size + 1];
  auto read_bytes = Serial.readBytesUntil('\n', buffer, serial_buffer_size);
  Serial.print("read: ");
  Serial.print(read_bytes, DEC);
  Serial.println(" bytes until newline");

  buffer[read_bytes] = '\0';
  parseCommand(buffer, read_bytes);
}

// the loop routine runs over and over again forever:
void loop() {
//  // read the input on analog pin 0:
//  int sensorValue = analogRead(A0);
//  // print out the value you read:
//  Serial.println(sensorValue);
//  delay(1);        // delay in between reads for stability

  // send data only when you receive data:
//  if (Serial.available() > 0) {
//          // read the incoming byte:
//          unsigned char incomingByte = Serial.read();
//
//          // say what you got:
//          Serial.print("I received: ");
//          Serial.println(incomingByte, DEC);
//  }
}
