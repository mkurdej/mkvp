#include <algorithm>
#include <iterator>

namespace mk {

template <class ForwardIt, class Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
void selection_sort(ForwardIt begin, ForwardIt end, Compare comp = {}) {
    for (auto i = begin; i != end; ++i) {
        std::iter_swap(i, std::min_element(i, end, comp));
    }
}

} // namespace mk
