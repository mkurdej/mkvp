#include <ArduinoLibcxx.h>
#include <array>
#include <chrono>
#include <cmath>

#define DECODE_KASEIKYO // Decode only this protocol.
#include <IRremote.h>
#define IR_RECEIVE_PIN 2

namespace chr = std::chrono;
using namespace std::literals;

constexpr uint8_t red_light_pin = 11;
constexpr uint8_t green_light_pin = 10;
constexpr uint8_t blue_light_pin = 9;

namespace mk {

struct rgb_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

constexpr rgb_color Red{255, 0, 0};
constexpr rgb_color Green{0, 255, 0};
constexpr rgb_color Blue{0, 0, 255};

constexpr rgb_color Cyan{0, 255, 255};
constexpr rgb_color Magenta{255, 0, 255};
constexpr rgb_color Yellow{255, 255, 0};

constexpr rgb_color Black{0, 0, 0};
constexpr rgb_color White{255, 255, 255};

constexpr rgb_color Raspberry{255, 255, 125};

namespace {

void RGB_color(uint8_t red_light_value, uint8_t green_light_value,
               uint8_t blue_light_value) {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void RGB_color(rgb_color c) {
  RGB_color(c.r, c.g, c.b);
}

void Delay(chr::milliseconds d) {
  delay(static_cast<int>(d.count()));
}

// TODO: Delay(chr::microseconds d)

} // namespace

constexpr std::array<std::pair<unsigned long, const char *>, 21>
    IrConstantCarMp3 = {{
        {0xA15EFF00, "3"},    {0xA55AFF00, "6"},    {0xAD52FF00, "8"},
        {0xB54AFF00, "9"},    {0xB847FF00, "CH+"},  {0xB946FF00, "CH"},
        {0xBA45FF00, "CH-"},  {0xBB44FF00, "|<<"},  {0xBC43FF00, ">||"},
        {0xBD42FF00, "7"},    {0xBF40FF00, ">>|"},  {0xE31CFF00, "5"},
        {0xE619FF00, "100+"}, {0xE718FF00, "2"},    {0xE916FF00, "0"},
        {0xEA15FF00, "+"},    {0xF20DFF00, "200+"}, {0xF30CFF00, "1"},
        {0xF609FF00, "EQ"},   {0xF708FF00, "4"},    {0xF807FF00, "-"},
    }};

constexpr std::array<std::pair<unsigned long, const char *>, 17>
    IrConstantCanon = {{
        {0xBF400681, "ON/OFF"},
        {0xBA450681, "AUTO PC"},
        {0xBD420681, "PC"},
        {0x9A650681, "HDMI"},
        {0xBB440681, "VIDEO"},
        {0xAB540681, "MUTE"},
        {0xAC530681, "VOL-"},
        {0xAD520681, "VOL+"},
        {0xBE410681, "MENU"},
        {0xB8470681, "^"},
        {0x96690681, "BACK"},
        {0xB6490681, "<"},
        {0xA55A0681, "OK"},
        {0xB54A0681, ">"},
        {0x956A0681, "HOME"},
        {0xB7480681, "v"},
        {0xA7580681, "BLANK"},
    }};

} // namespace mk

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    auto code_equal = [code](const auto &hex_name) {
      return hex_name.first == code;
    };
    auto it = std::find_if(mk::IrConstantCarMp3.cbegin(),
                           mk::IrConstantCarMp3.cend(), code_equal);
    if (it == mk::IrConstantCarMp3.cend()) {
      it = std::find_if(mk::IrConstantCanon.cbegin(),
                        mk::IrConstantCanon.cend(), code_equal);
    }

    Serial.print("0x");
    Serial.print(code, HEX);
    Serial.print(" -> ");
    if (it == mk::IrConstantCanon.cend()) {
      if (code == 0x0) {
        Serial.println("<repeat>");
      } else {
        Serial.println("UNKNOWN");
      }
    } else {
      Serial.println(it->second);
    }

    Serial.print("protocol: ");
    Serial.print(IrReceiver.decodedIRData.protocol);
    Serial.print(" -> ");
    Serial.println("");
    // Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));

    switch (code) {
    case 0xF30CFF00:
      mk::RGB_color(mk::Green);
      break;
    case 0xE718FF00:
      mk::RGB_color(mk::Red);
      break;
    case 0xA15EFF00:
      mk::RGB_color(mk::Blue);
      break;
    case 0xF708FF00:
      mk::RGB_color(mk::Cyan);
      break;
    case 0xE31CFF00:
      mk::RGB_color(mk::Magenta);
      break;
    case 0xA55AFF00:
      mk::RGB_color(mk::Yellow);
      break;
    case 0xBD42FF00:
      mk::RGB_color(mk::Raspberry);
      break;
    case 0xAD52FF00:
      mk::RGB_color(mk::White);
      break;
    case 0xB54AFF00:
      mk::RGB_color(mk::Black);
      break;
    }

    IrReceiver.resume();
  }
}
