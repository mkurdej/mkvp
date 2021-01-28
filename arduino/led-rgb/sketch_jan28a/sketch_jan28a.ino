#include <chrono.h>

namespace chr = std::chrono;
using namespace std::literals;

constexpr uint8_t red_light_pin = 11;
constexpr uint8_t green_light_pin = 10;
constexpr uint8_t blue_light_pin = 9;

struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

constexpr color Red{255, 0, 0};
constexpr color Green{0, 255, 0};
constexpr color Blue{0, 0, 255};
constexpr color White{255, 255, 255};
constexpr color Raspberry{255, 255, 125};
constexpr color Cyan{0, 255, 255};
constexpr color Magenta{255, 0, 255};
constexpr color Yellow{255, 255, 0};
constexpr color Black{0, 0, 0};

namespace {

void RGB_color(uint8_t red_light_value, uint8_t green_light_value,
               uint8_t blue_light_value) {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void RGB_color(color c) {
  RGB_color(c.r, c.g, c.b);
}

void Delay(chr::milliseconds d) {
  delay(static_cast<int>(d.count()));
}

} // namespace

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  RGB_color(Red);
  Delay(100ms);
  RGB_color(Green);
  Delay(100ms);
  RGB_color(Blue);
  Delay(100ms);
  RGB_color(Raspberry);
  Delay(1s);
  RGB_color(Cyan);
  Delay(1s);
  RGB_color(Magenta);
  Delay(1s);
  RGB_color(Yellow);
  Delay(1s);
  RGB_color(White);
  Delay(1s);
  RGB_color(Black);
  Delay(1s);
}
