#include <type_traits>

namespace mk {

template <bool B>
using bool_constant = integral_constant<bool, B>;

} // namespace mk