#include "arduino.hpp"
#include "test.h"

/*
#include "SevSeg.h"

#ifdef RESISTORS_ON_SEGMENTS
#  undef RESISTORS_ON_SEGMENTS
#endif
#define RESISTORS_ON_SEGMENTS 1
*/

using namespace arduino;

static const auto digit_on = state::high;
static const auto digit_off = state::low;

static const auto on = state::low;
static const auto off = state::high;
static const byte numDigits = 4;

/*
SevSeg sevseg; //Instantiate a seven segment object
static byte digitPins[] = {A0, A1, A2, A3};
static byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // , 10, 11, 12, 13
*/

static const digital_pin digitPins[numDigits] = {
    digital_pin::a0, digital_pin::a1, digital_pin::a2, digital_pin::a3};
static const digital_pin segmentPins[] = {
    digital_pin::d2, digital_pin::d3, digital_pin::d4, digital_pin::d5,
    digital_pin::d6, digital_pin::d7, digital_pin::d8, digital_pin::d9};

void choose_digit(uint8_t digit) { write(digitPins[digit], digit_on); }

void unchoose_digit(uint8_t digit) { write(digitPins[digit], digit_off); }

void clear(digital_pin dp, state s = off) {
  write(dp, on);
  for (auto sp : segmentPins) {
    write(sp, s);
  }
  write(dp, off);
}

void clear(state s = off) {
  for (auto dp : digitPins) {
    clear(dp, s);
  }
}

void setup() {
  // sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);

  for (auto p : digitPins) {
    set_pin_mode(p, io_mode::output);
  }
  for (auto p : segmentPins) {
    set_pin_mode(p, io_mode::output);
  }

  for (auto i = 0u; i < 1u; ++i) {
    clear(on);
    delay(1000);
    clear(off);
  }
}

int number = 0;

static const bool segments[10][8] = {
    {true, true, true, true, true, true, false, false},     // 0
    {false, true, true, false, false, false, false, false}, // 1
    {true, true, false, true, true, false, true, false},    // 2
    {true, true, true, true, false, false, true, false},    // 3
    {false, true, true, false, false, true, true, false},   // 4
    {true, false, true, true, false, true, true, false},    // 5
    {true, false, true, true, true, true, true, false},     // 6
    {true, true, true, false, false, false, false, false},  // 7
    {true, true, true, true, true, true, true, false},      // 8
    {true, true, true, true, false, true, true, false}      // 9
};

#define DISPLAY_BRIGHTNESS 5000

void set_digit(uint8_t n) {
  for (auto i = 0u; i < 8u; ++i) {
    write(segmentPins[i], segments[n % 10][i] ? on : off);
    delayMicroseconds(1);
  }

  delayMicroseconds(DISPLAY_BRIGHTNESS);
  // Display digit for fraction of a second (1us to 5000us, 500 is pretty good)
}

void set_number(int n) {
  auto beginTime = millis();

  // turn off all digits
  for (auto j = 0u; j < numDigits; ++j) {
    unchoose_digit(j);
  }

  for (auto i = 0u; i < numDigits; ++i) {
    /*
    for (auto j = 0u; j < numDigits; ++j) {
      choose_digit(j);
    }
    */
    choose_digit(numDigits - i - 1);
    auto d = n % 10;
    set_digit(d);
    unchoose_digit(numDigits - i - 1);
    n /= 10;

    // if (n <= 0) break;
  
    // turn off all digits
    for (auto j = 0u; j < numDigits; ++j) {
      unchoose_digit(j);
    }
  }

  while ((millis() - beginTime) < 10) {
    // wait
  }
}

void loop() {
#if 0
  sevseg.setNumber(number, /*decPlaces=*/0);
  set_number(8080);
  number++;
#endif

  /*
    choose_digit(0);
    unchoose_digit(1);
    choose_digit(2);
    unchoose_digit(3);
    set_digit(number);
    delay(1000);
  */

  // delay(1000);
  // set_number(number);
  set_number((millis() / 1000) % 10000);

  ++number;
}
