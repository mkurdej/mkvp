namespace std {

template <typename T, size_t N>
struct array {
  using value_type = T;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = pointer;
  using const_iterator = const_pointer;

  const_iterator begin() const {
     return _data;
  }

  const_iterator end() const {
     return _data + N;
  }

  iterator begin() {
     return _data;
  }

  iterator end() {
     return _data + N;
  }

  const_reference operator[](size_t i) const {
    return _data[i];
  }

  reference operator[](size_t i) {
    return _data[i];
  }
  
  const_reference front() const {
    return *begin();
  }

  reference front() {
    return *begin();
  }

  const_reference back() const {
    auto tmp = end();
    --tmp;
    return *tmp;
  }
  
  reference back() {
    auto tmp = end();
    --tmp;
    return *tmp;
  }

  const_pointer data() const {
    return _data;
  }

  pointer data() {
    return _data;
  }

  size_type size() const {
    return N;
  }

  bool empty() const {
    return 0 == size();
  }

  void fill(const T & value) {
    for (auto & v : _data) {
      v = value;
    }
  }

  T _data[N];
};

} // namespace std

