#include <qdb/util/counting_iterator.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(util)

struct counting_iterator_fixture
{
    qdb::util::counting_iterator cit;
};

BOOST_FIXTURE_TEST_SUITE(counting_iterator, counting_iterator_fixture)

BOOST_AUTO_TEST_CASE(default_constructed_count_is_zero)
{
    BOOST_CHECK_EQUAL(0u, cit.count);
}

BOOST_AUTO_TEST_CASE(count_does_not_change__when_prefix_operator_plus_plus_is_called)
{
    ++cit;
    BOOST_CHECK_EQUAL(0u, cit.count);
}

BOOST_AUTO_TEST_CASE(count_does_not_change__when_postfix_operator_plus_plus_is_called)
{
    cit++;
    BOOST_CHECK_EQUAL(0u, cit.count);
}

BOOST_AUTO_TEST_CASE(count_does_not_change__when_operator_star_is_called)
{
    cit++;
    BOOST_CHECK_EQUAL(0u, cit.count);
}

BOOST_AUTO_TEST_CASE(count_increments__when_operator_equal_is_called)
{
    cit = 132;
    BOOST_CHECK_EQUAL(1u, cit.count);
}

BOOST_AUTO_TEST_CASE(count_increments__when_copy_is_called)
{
    const std::vector<int> v = {1, 2, 3, 4, 5};
    cit = std::copy(v.begin(), v.end(), cit);
    BOOST_CHECK_EQUAL(v.size(), cit.count);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
