#include <algorithm>
#include <iterator>
#include <limits>

namespace mk {

namespace detail {

template <typename IntegralType>
bool is_odd(IntegralType v) {
  return v & 1;
}

} // namespace detail

template <typename Iterator,
          typename ValueType =
              typename std::iterator_traits<Iterator>::value_type>
struct value_and_range {
  ValueType value;
  Iterator begin, end;
};

// Function to return maximum product of a subset of given array
template <typename Iterator, typename ValueType = typename std::iterator_traits<
                                 Iterator>::value_type>
value_and_range<Iterator> maximum_subset_product(Iterator first,
                                                 Iterator last) {
  using result_type = value_and_range<Iterator>;

  const auto n = std::distance(first, last);

  if (n == 0) return result_type{{}, first, last};
  if (n == 1) return result_type{*first, first, last};

  auto product = ValueType{1}; // to store maximum product subset

  // stores the negative element having minimum absolute value in the set
  auto abs_min_so_far = std::numeric_limits<ValueType>::max();

  size_t negative = 0; // maintain count of negative elements in the set
  size_t positive = 0; // maintain count of positive elements in the set

  bool contains_zero = false;

  Iterator start = first, end = last;

  for (Iterator it = first; it != last; ++it) {
    if (*it < 0) {
      ++negative;
      abs_min_so_far = std::min(abs_min_so_far, std::abs(*it));
    } else if (*it > 0) {
      ++positive;
    }

    if (*it == 0) {
      contains_zero = true;
    } else {
      product = product * (*it);
    }
  }

  // if odd number of negative elements are present, exclude the negative
  // element having minimum absolute value from the subset
  if (detail::is_odd(negative)) {
    product = product / -abs_min_so_far;
  }

  // special case - set contains one negative element and one or more zeroes
  if (negative == 1 && !positive && contains_zero) {
    product = ValueType{0};
  }

  // return maximum product
  return result_type{product, start, end};
}

} // namespace mk

#include <iostream>

int main() {
  int arr[] = {-6, 4, -5, 8, -10, 0, 8};

  auto res = mk::maximum_subset_product(std::cbegin(arr), std::cend(arr));
  std::cout << "The maximum product of a subset is " << res.value << '\n';

  return 0;
}
