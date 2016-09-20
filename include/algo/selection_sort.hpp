#include <algorithm>

namespace mk {

template <class ForwardIt, class Compare = std::less<>>
void selection_sort(ForwardIt begin, ForwardIt end, Compare comp = {})
{
    for (auto i = begin; i != end; ++i) {
        std::iter_swap(i, std::min_element(i, end, comp));
    }
}

} // namespace mk
