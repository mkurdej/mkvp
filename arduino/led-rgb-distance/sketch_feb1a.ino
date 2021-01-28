#include <chrono.h>
// #include <algorithm> // TODO: no wchar.h on Arduino

namespace chr = std::chrono;
using namespace std::literals;

constexpr uint8_t red_light_pin = 11;
constexpr uint8_t green_light_pin = 10;
constexpr uint8_t blue_light_pin = 9;

constexpr uint8_t trigger_pin = 7;
constexpr uint8_t echo_pin = 6;

template <typename T>
constexpr T clamp(const T &v, const T &lo, const T &hi) {
  return (v < lo) ? lo : (hi < v) ? hi : v;
}

template <typename T>
constexpr T abs(const T &v) {
  return (v < T(0)) ? -v : v;
}

namespace mk {

template <size_t Period, size_t Smoothing = 2, typename T>
constexpr T exponential_average(const T &value, const T &old_value) {
  constexpr float weight = static_cast<float>(Smoothing) / (1 + Period);
  return (value * weight) + (old_value * (1.0 - weight));
}

struct rgb_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct hsv_color {
  uint16_t h; // [0, 360]
  uint8_t s;  // [0, 100]
  uint8_t v;  //[0, 100]
};

rgb_color HSVtoRGB(hsv_color hsv) {
  //   if (H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
  //     cout << "The givem HSV values are not in valid range" << endl;
  //     return;
  //   }
  float s = hsv.s / 100.0;
  float v = hsv.v / 100.0;
  float C = s * v;
  float X = C * (1 - abs(fmod(hsv.h / 60.0, 2) - 1));
  float m = v - C;

  float r, g, b;
  if (hsv.h >= 0 && hsv.h < 60) {
    r = C, g = X, b = 0;
  } else if (hsv.h >= 60 && hsv.h < 120) {
    r = X, g = C, b = 0;
  } else if (hsv.h >= 120 && hsv.h < 180) {
    r = 0, g = C, b = X;
  } else if (hsv.h >= 180 && hsv.h < 240) {
    r = 0, g = X, b = C;
  } else if (hsv.h >= 240 && hsv.h < 300) {
    r = X, g = 0, b = C;
  } else {
    r = C, g = 0, b = X;
  }

  rgb_color res;
  res.r = (r + m) * 255;
  res.g = (g + m) * 255;
  res.b = (b + m) * 255;
  return res;
}

constexpr rgb_color Red{255, 0, 0};
constexpr rgb_color Green{0, 255, 0};
constexpr rgb_color Blue{0, 0, 255};
constexpr rgb_color White{255, 255, 255};
constexpr rgb_color Raspberry{255, 255, 125};
constexpr rgb_color Cyan{0, 255, 255};
constexpr rgb_color Magenta{255, 0, 255};
constexpr rgb_color Yellow{255, 255, 0};
constexpr rgb_color Black{0, 0, 0};

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
} // namespace mk

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
}

long measure_distance() {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  auto duration = chr::microseconds{pulseIn(echo_pin, HIGH)};
  // Speed of sound in air: 343 m/s.
  // Hence, in 1s, the sound travels 0.00291545 m.
  // Need to /2.0, because go and forth.
  auto distance_cm = duration.count() / (29.1545 * 2);
  return distance_cm;
}

long smoothed_distance = 0;

void loop() {
  auto distance = measure_distance();
  Serial.print(distance);
  Serial.print(" cm\t");

  smoothed_distance =
      mk::exponential_average</*Period=*/10>(distance, smoothed_distance);
  Serial.print(smoothed_distance);
  Serial.print(" cm\t");

  // smoothed_distance = (smoothed_distance % 72) * 5;
  smoothed_distance %= 360;

  auto rgb = mk::HSVtoRGB(
      mk::hsv_color{static_cast<uint16_t>(smoothed_distance), 100, 50});
  Serial.print("\t(R=");
  Serial.print(rgb.r);
  Serial.print(",\tG=");
  Serial.print(rgb.g);
  Serial.print(",\tB=");
  Serial.print(rgb.b);
  Serial.println(")");

  mk::RGB_color(rgb);
  mk::Delay(50ms);
}
