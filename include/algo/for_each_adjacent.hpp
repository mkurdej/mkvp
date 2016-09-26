#pragma once

namespace mk {

template <typename FwIter, typename Func>
void for_each_adjacent(FwIter first, FwIter last, Func f) {
  if (first == last) return;

  FwIter trailer = first;
  ++first;
  for (; first != last; ++first, ++trailer) {
    f(*trailer, *first);
  }
}

} // namespace mk
