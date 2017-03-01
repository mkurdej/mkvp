#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>

namespace mk {

template <class ForwardIt, class Compare = std::less<>>
void quick_sort(ForwardIt first, ForwardIt last, Compare cmp = Compare{}) {
    auto const N = std::distance(first, last);
    if (N <= 1) return;

    auto const pivot = *std::next(first, N / 2);
    auto const middle1 = std::partition(first, last, [=](auto const& elem){ 
        return cmp(elem, pivot); 
    });
    auto const middle2 = std::partition(middle1, last, [=](auto const& elem){ 
        return !cmp(pivot, elem);
    });

    quick_sort(first, middle1, cmp);
    assert(std::is_sorted(first, middle1, cmp));
    quick_sort(middle2, last, cmp);
    assert(std::is_sorted(middle2, last, cmp));
}

} // namespace mk
