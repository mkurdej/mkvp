namespace std {

template <typename T1, typename T2>
class pair
{
public:
  pair()
  {
  }

  pair(const T1 & t1, const T2 & t2) : first(t1), second(t2)
  {
  }

  T1 first;
  T2 second;
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1 & t1, const T2 & t2) {
  return pair<T1, T2>(t1, t2);
}

} // namespace std

