#include <iterator/counting_iterator.hpp>
#include <catch.hpp>

TEST_CASE("starting from low state", "[counting iterator]") {
  mk::counting_iterator cit;

  SECTION("default_constructed_count_is_zero") {
    REQUIRE(0u == cit.count);
  }

  SECTION("count_does_not_change__when_prefix_operator_plus_plus_is_called") {
    ++cit;
    REQUIRE(0u == cit.count);
  }

  SECTION("count_does_not_change__when_postfix_operator_plus_plus_is_called") {
    cit++;
    REQUIRE(0u == cit.count);
  }

  SECTION("count_does_not_change__when_operator_star_is_called") {
    cit++;
    REQUIRE(0u == cit.count);
  }

  SECTION("count_increments__when_operator_equal_is_called") {
    cit = 132;
    REQUIRE(1u == cit.count);
  }

  SECTION("count_increments__when_copy_is_called") {
    const std::vector<int> v = {1, 2, 3, 4, 5};
    cit = std::copy(v.begin(), v.end(), cit);
    REQUIRE(v.size() == cit.count);
  }
}
