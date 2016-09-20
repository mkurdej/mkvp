#include <algorithm>
#include <cassert>
#include <functional>

namespace mk {

template <class BiDirIt, class Compare = std::less<>>
void merge_sort(BiDirIt first, BiDirIt last, Compare cmp = Compare{})
{
    auto const N = std::distance(first, last);
    if (N <= 1) return;                   

    auto const middle = std::next(first, N / 2);

    merge_sort(first, middle, cmp);
    assert(std::is_sorted(first, middle, cmp));
    merge_sort(middle, last, cmp);
    assert(std::is_sorted(middle, last, cmp));

    std::inplace_merge(first, middle, last, cmp);
    assert(std::is_sorted(first, last, cmp));
}

} // namespace mk
