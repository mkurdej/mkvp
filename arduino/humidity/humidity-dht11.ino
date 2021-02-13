#include <ArduinoLibcxx.h>
// #include <array>
#include <chrono>
// #include <cmath>

#include <Adafruit_Sensor.h>
#include <DHT.h>
// Set DHT pin:
#define DHTPIN 3
// Set DHT type, uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Initialize DHT sensor for normal 16mhz Arduino:
// DHT dht = DHT(DHTPIN, DHTTYPE);

namespace mk {

template <typename Rep, typename PreDifferenceToCelsius = std::ratio<0>,
          typename RatioToCelsius = std::ratio<1>,
          typename PostDifferenceToCelsius = std::ratio<0>>
struct temperature {
  using representation = Rep;
  using ratio = RatioToCelsius;
  using pre_difference = PreDifferenceToCelsius;
  using post_difference = PostDifferenceToCelsius;

  explicit temperature(Rep cnt) : _count{cnt} {}

  Rep count() {
    return _count;
  }

private:
  Rep _count;
};

using degrees_celsius = temperature<float>;
using degrees_fahrenheit =
    temperature<float, std::ratio<0>, std::ratio<18, 10>, std::ratio<32>>;

using Pin = uint8_t;

struct DHT {
  enum class Type : uint8_t {
    Dht11 = DHT11,
    Dht21 = DHT21, // AM2301
    Dht22 = DHT22  // AM2302
  };

  // TODO: to_underlying
  DHT(Pin p, Type t) : _dht((uint8_t)p, (uint8_t)t) {}

  DHT(Pin p, Type t, uint8_t count) : _dht((uint8_t)p, (uint8_t)t, count) {}

  void begin() {
    return _dht.begin();
  }

  float read_humidity() {
    return _dht.readHumidity();
  }

  degrees_celsius read_temperature_celsius() {
    return degrees_celsius{_dht.readTemperature()};
  }

  degrees_fahrenheit read_temperature_fahrenheit() {
    return degrees_fahrenheit{_dht.readTemperature(true)};
  }

  degrees_celsius compute_heat_index(degrees_celsius t, float humidity) {
    return degrees_celsius{_dht.computeHeatIndex(t.count(), humidity, false)};
  }

  degrees_fahrenheit compute_heat_index(degrees_fahrenheit t, float humidity) {
    return degrees_fahrenheit{_dht.computeHeatIndex(t.count(), humidity)};
  }

private:
  ::DHT _dht;
};

template <typename To, typename From>
To unit_cast(From v) {
  using Rep = typename To::representation;
  using Ratio = typename To::ratio;
  using PreDiff = typename To::pre_difference;
  using PostDiff = typename To::post_difference;

  return To{                                                    //
            (v.count() + Rep(PreDiff::num) / Rep(PreDiff::den)) //
                * Ratio::num / Ratio::den +
            Rep(PostDiff::num) / Rep(PostDiff::den)};
}

// template <typename To, typename From>
// To unit_cast(From v);

// template <>
// degrees_fahrenheit
// unit_cast</*To=*/degrees_fahrenheit, /*From=*/degrees_celsius>(
//     degrees_celsius v) {
//   return degrees_fahrenheit{v.count() * 1.8 + 32.0};
// }

} // namespace mk

mk::DHT dht(DHTPIN, mk::DHT::Type::Dht11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements:
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read the humidity in %:
  auto hum = dht.read_humidity();
  // Read the temperature as Celsius:
  auto tempC = dht.read_temperature_celsius();

  // Check if any reads failed and exit early (to try again):
  if (isnan(hum) || isnan(tempC.count())) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  auto hic = dht.compute_heat_index(tempC, hum);

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" % ");

  Serial.print("Temperature: ");
  Serial.print(tempC.count());
  Serial.print(" \xC2\xB0");
  Serial.print("C | ");

  Serial.print("Heat index: ");
  Serial.print(hic.count());
  Serial.print(" \xC2\xB0");
  Serial.print("C");

  Serial.println("");
}
