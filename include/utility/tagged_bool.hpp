#pragma once

namespace mk {
namespace disable_adl {

template <typename Tag>
class tagged_bool {
  template <typename /*OtherTag*/>
  friend class tagged_bool;

public:
  constexpr explicit tagged_bool(bool v) : value{v} {}

  constexpr explicit tagged_bool(int) = delete;
  constexpr explicit tagged_bool(double) = delete;
  constexpr explicit tagged_bool(void *) = delete;

  template <typename OtherTag>
  constexpr explicit tagged_bool(tagged_bool<OtherTag> b) : value{b.value} {}

  constexpr explicit operator bool() const {
    return value;
  }
  constexpr tagged_bool operator!() const {
    return tagged_bool{!value};
  }

  friend constexpr bool operator==(tagged_bool l, tagged_bool r) {
    return l.value == r.value;
  }
  friend constexpr bool operator!=(tagged_bool l, tagged_bool r) {
    return l.value != r.value;
  }

private:
  bool value;
};

} // namespace disable_adl

using disable_adl::tagged_bool

} // namespace mk