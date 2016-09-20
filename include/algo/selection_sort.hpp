#include <algorithm>
#include <iterator>

namespace mk {

template <class ForwardIt, class Compare>
void selection_sort(ForwardIt begin, ForwardIt end, Compare comp)
{
    for (auto i = begin; i != end; ++i) {
        std::iter_swap(i, std::min_element(i, end, comp));
    }
}

template <class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    using value_type = typename std::iterator_traits<ForwardIt>::value_type;
    selection_sort(begin, end, std::less<value_type>());
}

} // namespace mk
