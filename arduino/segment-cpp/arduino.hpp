#pragma once

// #include <type_traits>

namespace arduino
{

enum class state : uint8_t {
  low = LOW,
  high = HIGH
};

enum class io_mode : uint8_t {
  input = INPUT,
  output = OUTPUT,
  input_pullup = INPUT_PULLUP
};

enum class bit_order : uint8_t {
  lsb_first = LSBFIRST,
  msb_first = MSBFIRST
};

enum class state_change : uint8_t {
  any = CHANGE,
  falling = FALLING,
  rising = RISING
};

enum class digital_pin : uint8_t {
  a0 = A0,
  a1 = A1,
  a2 = A2,
  a3 = A3,
  a4 = A4,
  a5 = A5,
  d0 = 0,
  rx = d0,
  d1 = 1,
  tx = d1,
  d2 = 2,
  d3 = 3,
  d4 = 4,
  d5 = 5,
  d6 = 6,
  d7 = 7,
  d8 = 8,
  d9 = 9,
  d10 = 10,
  d11 = 11,
  d12 = 12,
  d13 = 13
};

enum class digital_pwm_pin : uint8_t {
  pwm3 = 3,
  pwm5 = 5,
  pwm6 = 6,
  pwm9 = 9,
  pwm10 = 10,
  pwm11 = 11
};

enum class analog_pin : uint8_t {
  a0 = A0,
  a1 = A1,
  a2 = A2,
  a3 = A3,
  a4 = A4,
  a5 = A5
};

//template <typename Enum>
//static auto as_integer(Enum e) -> std::underlying_type_t<Enum> {
//  using underlying = std::underlying_type_t<Enum>;
//  return static_cast<underlying>(e);
//}

template <typename Enum>
static int as_int(Enum e) {
  return static_cast<int>(e);
}

template <typename Enum>
static int as_uint8(Enum e) {
  return static_cast<uint8_t>(e);
}

static inline void set_pin_mode(digital_pin p, io_mode m) {
  return pinMode(as_uint8(p), as_uint8(m));
}

static inline int read(digital_pin p) {
  return digitalRead(as_uint8(p));
}

static inline void write(digital_pin p, uint8_t data) {
  return digitalWrite(as_uint8(p), data);
}

static inline void write(digital_pin p, state s) {
  return digitalWrite(as_uint8(p), as_uint8(s));
}

static inline int read(analog_pin p) {
  return analogRead(as_uint8(p));
}

static inline void write(analog_pin p, int data) {
  return analogWrite(as_uint8(p), data);
}

static inline void write(analog_pin p, state s) {
  return analogWrite(as_uint8(p), as_int(s));
}

//static inline void reference(uint8_t mode) {
//  return pinMode(as_uint8(p), m);
//}

// TODO:
// delay

} // namespace arduino
