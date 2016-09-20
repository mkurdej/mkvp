#include <algorithm>
#include <iterator>

namespace mk {

template <typename RandomIt, typename Compare>
void insertion_sort(RandomIt begin, RandomIt end, Compare comp) {
    for (auto i = begin; i != end; ++i) {
        std::rotate(std::upper_bound(begin, i, *i, comp), i, std::next(i));
    }
}
 
template <typename RandomIt>
void insertion_sort(RandomIt begin, RandomIt end) {
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    insertion_sort(begin, end, std::less<value_type>());
}

} // namespace mk
