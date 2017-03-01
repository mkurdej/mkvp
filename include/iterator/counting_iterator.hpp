#include <iterator>

namespace qdb
{
namespace util
{

struct counting_iterator : std::iterator<std::output_iterator_tag, void *>
{
    using this_type = counting_iterator;

    size_t count = 0;

    this_type & operator++()
    {
        return *this;
    }

    this_type & operator++(int)
    {
        return *this;
    }

    this_type & operator*()
    {
        return *this;
    }

    template <typename T>
    this_type & operator=(T)
    {
        ++count;
        return *this;
    }
};

} // namespace util
} // namespace qdb