//#include <functional>

namespace std
{

template <typename T = void>
struct less
{
  constexpr bool operator()(const T &lhs, const T &rhs) const 
  {
      return lhs < rhs;
  }
};

template <>
struct less<void>
{
  template <typename T>
  constexpr bool operator()(const T &lhs, const T &rhs) const 
  {
      return lhs < rhs;
  }
};

template <class T, class Compare = less<>>
constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp = Compare());

template<class T, class Compare>
constexpr const T& clamp(const T& val, const T& lo, const T& hi, Compare comp)
{
    return assert(!comp(hi, lo)),
        comp(val, lo) ? lo : comp(hi, val) ? hi : val;
}

} // namespace std

