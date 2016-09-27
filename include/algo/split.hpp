#pragma once

#include <algorithm>

namespace mk {

template <typename InIter, typename T, typename Func>
void split(InIter first, InIter last, const T &t, Func f) {
  while (true) {
    InIter found = std::find(first, last, t);
    f(first, found);

    if (found == last) break;
    first = ++found;
  }
}

} // namespace mk
