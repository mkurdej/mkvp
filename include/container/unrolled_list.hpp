#pragma once

//#include <algorithm>

namespace mk {

template <typename T, typename N, typename Allocator = std::allocator<T>>
class unrolled_list {
public:
  class iterator;
  class const_iterator;
  class reverse_iterator;
  class const_reverse_iterator;

  T &front();
  const T &front() const;
  T &back();
  const T &back() const;

  size_t size() const {
    return _size;
  }

  size_t max_size() const;

  size_t empty() const {
    return size() == 0;
  }

  void clear();
  void insert();
  void emplace();
  void erase();

  void push_front();
  void push_back();
  void emplace_front();
  void emplace_back();
  void pop_front();
  void pop_back();

  void resize(size_t new_size);

  void merge();
  void splice();
  void remove();
  void remove_if();
  void reverse();
  void unique();
  void sort();

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crbegin() const;
  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_reverse_iterator crend() const;

  friend bool operator==(const unrolled_list &lhs, const unrolled_list &rhs);
  friend bool operator!=(const unrolled_list &lhs, const unrolled_list &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const unrolled_list &lhs, const unrolled_list &rhs);
  friend bool operator<=(const unrolled_list &lhs, const unrolled_list &rhs) {
    return (lhs < rhs) || (lhs == rhs);
  }

  friend bool operator>(const unrolled_list &lhs, const unrolled_list &rhs);
  friend bool operator>=(const unrolled_list &lhs, const unrolled_list &rhs) {
    return (lhs > rhs) || (lhs == rhs);
  }

private:
  size_t _size;

  struct node;
  struct node {
    node *_next;
    node *_prev;
    size_t _count;
    T[N] _elems;
  };
};

} // namespace mk
