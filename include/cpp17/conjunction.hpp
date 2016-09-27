#include <type_traits>

namespace mk {

template <class...>
struct conjunction : std::true_type {};

template <class B1>
struct conjunction : B1 {};

template <class B1, class... Bn>
struct conjunction
    : std::conditional_t<B1::value != false, conjunction<Bn...>, B1> {};

} // namespace mk