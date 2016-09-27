#include "bool_constant.hpp"

namespace mk {

template <class B>
struct negation : bool_constant<!B::value> {};

} // namespace mk