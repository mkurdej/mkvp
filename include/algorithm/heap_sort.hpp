#include <algorithm>
#include <cassert>
#include <functional>

namespace mk {

template <class RandomIt, class Compare = std::less<>>
void heap_sort(RandomIt first, RandomIt last, Compare cmp = {})
{
    std::make_heap(first, last, cmp);
    assert(std::is_heap(first, last, cmp));
    std::sort_heap(first, last, cmp);
    assert(std::is_sorted(first, last, cmp));
}

} // namespace mk
