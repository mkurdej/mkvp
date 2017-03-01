#pragma once

#include <cstddef>
#include <memory>
#include <utility>

namespace mk {
namespace disable_adl {

template <typename Ptr>
class not_null {
  Ptr ptr;

public:
  explicit not_null(Ptr p) : ptr(::std::move(p)) {}
  explicit not_null(::std::nullptr_t) = delete;

  Ptr &get_nested() {
    return ptr;
  }

  Ptr const &get_nested() const {
    return ptr;
  }

  auto operator*() const noexcept(noexcept(*ptr)) -> decltype(*ptr) {
    return *ptr;
  }

  auto operator*() noexcept(noexcept(*ptr)) -> decltype(*ptr) {
    return *ptr;
  }

  auto operator-> () const noexcept(noexcept(::std::addressof(*ptr)))
      -> decltype(::std::addressof(*ptr)) {
    return ::std::addressof(*ptr);
  }

  auto operator-> () noexcept(noexcept(::std::addressof(*ptr)))
      -> decltype(::std::addressof(*ptr)) {
    return ::std::addressof(*ptr);
  }
};

template <typename Ptr>
not_null<Ptr> as_not_null(Ptr p) {
  return not_null<Ptr>{::std::move(p)};
}

void as_not_null(::std::nullptr_t) = delete;

} // namespace disable_adl

using disable_adl::not_null;
using disable_adl::as_not_null;

} // namespace mk