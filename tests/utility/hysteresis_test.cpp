#include <qdb/util/hysteresis.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(util)
BOOST_AUTO_TEST_SUITE(hysteresis)

struct hysteresis_low_fixture
{
protected:
    qdb::hysteresis<int> _h{10, 20, false};
};

struct hysteresis_high_fixture
{
protected:
    qdb::hysteresis<int> _h{10, 20, true};
};

BOOST_FIXTURE_TEST_SUITE(low, hysteresis_low_fixture)

BOOST_AUTO_TEST_CASE(starts_in_false)
{
    BOOST_CHECK_EQUAL(false, _h(15));
}

BOOST_AUTO_TEST_CASE(below_low)
{
    BOOST_CHECK_EQUAL(false, _h(5));
}

BOOST_AUTO_TEST_CASE(below_low_then_low)
{
    BOOST_REQUIRE_EQUAL(false, _h(5));
    BOOST_CHECK_EQUAL(false, _h(10));
}

BOOST_AUTO_TEST_CASE(below_low_then_middle)
{
    BOOST_REQUIRE_EQUAL(false, _h(5));
    BOOST_CHECK_EQUAL(false, _h(15));
    BOOST_CHECK_EQUAL(true, _h(30));
}

BOOST_AUTO_TEST_CASE(below_low_then_high)
{
    BOOST_REQUIRE_EQUAL(false, _h(5));
    BOOST_CHECK_EQUAL(false, _h(20));
}

BOOST_AUTO_TEST_CASE(above_high)
{
    BOOST_CHECK_EQUAL(true, _h(25));
}

BOOST_AUTO_TEST_CASE(above_high_then_middle)
{
    BOOST_REQUIRE_EQUAL(true, _h(25));
    BOOST_CHECK_EQUAL(true, _h(15));
    BOOST_CHECK_EQUAL(false, _h(5));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(high, hysteresis_high_fixture)

BOOST_AUTO_TEST_CASE(starts_in_true)
{
    BOOST_CHECK_EQUAL(true, _h(15));
}

BOOST_AUTO_TEST_CASE(complex)
{
    BOOST_CHECK_EQUAL(true, _h(15));
    BOOST_CHECK_EQUAL(true, _h(20));
    BOOST_CHECK_EQUAL(true, _h(25));
    BOOST_CHECK_EQUAL(true, _h(20));
    BOOST_CHECK_EQUAL(true, _h(15));
    BOOST_CHECK_EQUAL(true, _h(10));
    BOOST_CHECK_EQUAL(false, _h(5));
    BOOST_CHECK_EQUAL(false, _h(10));
    BOOST_CHECK_EQUAL(false, _h(20));
    BOOST_CHECK_EQUAL(true, _h(21));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
