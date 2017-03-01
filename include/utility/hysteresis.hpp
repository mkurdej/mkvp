#pragma once

namespace qdb
{

template <typename T>
struct hysteresis
{
    hysteresis(const T & low, const T & high, bool initial_state) : _low(low), _high(high), _state(initial_state)
    {
    }

    bool operator()(const T & v)
    {
        if (v < _low)
        {
            _state = false;
        }
        else if (_high < v)
        {
            _state = true;
        }

        return _state;
    }

private:
    const T _low, _high;
    bool _state;
};

} // namespace qdb
