#include <utility/hysteresis.hpp>
#include <catch.hpp>

TEST_CASE("starting from low state", "[hysteresis]") {
  mk::hysteresis<int> _h{10, 20, false};

  REQUIRE(_h.state() == false);

  SECTION("starts_in_false") {
    REQUIRE(false == _h(15));
  }

  SECTION("below_low") {
    REQUIRE(false == _h(5));
  }

  SECTION("below_low_then_low") {
    REQUIRE(false == _h(5));

    REQUIRE(false == _h(10));
  }

  SECTION("below_low_then_middle") {
    REQUIRE(false == _h(5));

    REQUIRE(false == _h(15));
    REQUIRE(true == _h(30));
  }

  SECTION("below_low_then_high") {
    REQUIRE(false == _h(5));

    REQUIRE(false == _h(20));
  }

  SECTION("above_high") {
    REQUIRE(true == _h(25));
  }

  SECTION("above_high_then_middle") {
    REQUIRE(true == _h(25));

    REQUIRE(true == _h(15));
    REQUIRE(false == _h(5));
  }
}

TEST_CASE("starting from high state", "[hysteresis2]") {
  mk::hysteresis<int> _h{10, 20, true};

  REQUIRE(_h.state() == true);

  SECTION("starts_in_true") {
    REQUIRE(true == _h(15));
  }

  SECTION("complex") {
    REQUIRE(true == _h(15));
    REQUIRE(true == _h(20));
    REQUIRE(true == _h(25));
    REQUIRE(true == _h(20));
    REQUIRE(true == _h(15));
    REQUIRE(true == _h(10));
    REQUIRE(false == _h(5));
    REQUIRE(false == _h(10));
    REQUIRE(false == _h(20));
    REQUIRE(true == _h(21));
  }
}
