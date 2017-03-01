#pragma once

#include <type_traits>

namespace mk {
namespace disable_adl {

template <typename T>
class out_parameter {
  static_assert(std::is_lvalue_reference<T>::value,
                "only references to non-const");
  static_assert(!std::is_const<typename std::remove_reference<T>::type>::value,
                "only references to non-const");
  T &_ref;

public:
  explicit out_parameter(T &ref) : _ref(ref) {}
  T &get() {
    return _ref;
  }
};

template <typename T>
out_parameter<T &> out(T &ref) {
  static_assert(!std::is_const<T>::value, "only references to non-const");
  return out_parameter<T &>(ref);
}

} // namespace disable_adl

using disable_adl::out_parameter;
using disable_adl::out;

} // namespace mk