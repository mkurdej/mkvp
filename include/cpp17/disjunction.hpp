#include <type_traits>

namespace mk {

template <class...>
struct disjunction : std::false_type {};

template <class B1>
struct disjunction : B1 {};

template <class B1, class... Bn>
struct disjunction
    : std::conditional_t<B1::value != false, B1, disjunction<Bn...>> {};

} // namespace mk
