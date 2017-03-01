#pragma once

#include <boost/range/irange.hpp>

namespace qdb
{

template <typename T, typename StepSize>
auto irange(T lower, T upper, StepSize step_size) -> decltype(boost::irange(lower, upper, step_size))
{
    return boost::irange(lower, upper, step_size);
}

template <typename T>
auto irange(T lower, T upper) -> decltype(boost::irange(lower, upper))
{
    return boost::irange(lower, upper);
}

template <typename T>
auto irange(T upper) -> decltype(boost::irange(static_cast<T>(0), upper))
{
    return boost::irange(static_cast<T>(0), upper);
}

} // namespace qdb
