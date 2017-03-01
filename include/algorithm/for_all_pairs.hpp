#pragma once

namespace mk {

template <typename FwIter, typename Func>
void for_all_pairs(FwIter first, FwIter last, Func f) {
  if (first == last) return;

  FwIter trailer = first;
  ++first;
  for (; first != last; ++first, ++trailer) {
    for (FwIter it = first; it != last; ++it) {
      f(*trailer, *it);
    }
  }
}

} // namespace mk
