#include <algorithm>
#include <iterator>

namespace mk {

template <typename RandomIt, typename Compare = std::less<>>
void insertion_sort(RandomIt begin, RandomIt end, Compare comp = {}) {
  for (auto i = begin; i != end; ++i) {
    std::rotate(std::upper_bound(begin, i, *i, comp), i, std::next(i));
  }
}

} // namespace mk
