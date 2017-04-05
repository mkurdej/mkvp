#include <algorithm>
#include <limits>
#include <tuple>

namespace mk {

namespace detail {

template <typename IntegralType>
bool is_odd(IntegralType v) {
  return v & 1;
}

} // namespace detail

// Function to return maximum product of a subset of given array
template <typename Iterator, typename ValueType = typename std::iterator_traits<
                                 Iterator>::value_type>
std::tuple<ValueType, Iterator, Iterator>
maximum_subset_product(Iterator first, Iterator last) {
  const auto n = std::distance(first, last);

  if (n == 0) return std::make_tuple(ValueType{}, first, last);
  if (n == 1) return std::make_tuple(*first, first, last);

  int product = 1; // to store maximum product subset

  // stores the negative element having minimum absolute value in the set
  int abs_min_so_far = std::numeric_limits<int>::max();

  int negative = 0; // maintain count of negative elements in the set
  int positive = 0; // maintain count of positive elements in the set

  bool contains_zero = false;

  Iterator start = first, end = last;

  // traverse the given array
  for (Iterator it = first; it != last; ++it) {
    // if current element is negative
    if (*it < 0) {
      ++negative;
      abs_min_so_far = std::min(abs_min_so_far, std::abs(*it));
    }
    // if current element is positive
    else if (*it > 0) {
      ++positive;
    }

    // if current element is zero
    if (*it == 0) {
      contains_zero = true;
    } else {
      product = product * (*it);
    }
  }

  // if odd number of negative elements are present, exclude the negative
  // element having minimum absolute value from the subset
  if (detail::is_odd(negative)) product = product / -abs_min_so_far;

  // special case - set contains one negative element and one or more zeroes
  if (negative == 1 && !positive && contains_zero) product = 0;

  // return maximum product
  return std::make_tuple(product, start, end);
}

} // namespace mk

#include <cstdio>

int main() {
  int arr[] = {-6, 4, -5, 8, -10, 0, 8};

  auto res = mk::maximum_subset_product(std::begin(arr), std::end(arr));
  printf("The maximum product of a subset is %d", std::get<0>(res));

  return 0;
}
