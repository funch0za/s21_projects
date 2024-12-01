#ifndef MAP_H
#define MAP_H

#include <initializer_list>
#include <stdexcept>

#include "../tree/tree.h"

namespace s21 {
template <class T1, class T2>
class map : public tree<T1, T2> {
 public:
  class map_iterator;
  class const_map_iterator;

  using key_t = T1;
  using value_t = T2;
  using pair_t = std::pair<const key_t, value_t>;
  using tree_node = typename tree<T1, T2>::node *;
  using reference = pair_t &;
  using const_reference = const pair_t &;

  using iterator = map_iterator;
  using const_iterator = const_map_iterator;

  using size_t = std::size_t;

  // Map Member functions
  map() : tree<T1, T2>() {}

  map(std::initializer_list<pair_t> const &items) {
    for (const auto &elem : items) {
      tree<T1, T2>::insert(elem.first, elem.second);
    }
  }

  map(const map &m) : map() {
    for (const auto &elem : m) {
      tree<T1, T2>::insert(elem.first, elem.second);
    }
  }

  map(map &&m) noexcept : map() {
    if (this != &m) {
      tree<T1, T2>::root_ = m.root_;
      m.root_ = nullptr;
    }
  }

  map &operator=(map &&m) noexcept {
    if (this != &m) {
      clear();
      tree<T1, T2>::root_ = m.root_;
      m.root_ = nullptr;
    }
    return *this;
  }

  // Map Iterators
  iterator begin() const {
    return map_iterator(tree<T1, T2>::find_min(tree<T1, T2>::root_));
  }

  iterator end() const { return map_iterator(nullptr); }

  class map_iterator {
   public:
    friend class map;

    using ptr_t = tree_node;

    explicit map_iterator(ptr_t ptr) : ptr_(ptr), past_ptr_(nullptr) {}

    reference operator*() const { return {ptr_->key_, ptr_->value_}; }

    map_iterator &operator++() {
      ptr_ = tree<T1, T2>::next(ptr_);
      return *this;
    }

    map_iterator &operator--() {
      ptr_ = tree<T1, T2>::prev(ptr_);
      return *this;
    }

    bool operator==(const map_iterator &other) const {
      return other.ptr_ == ptr_;
    }

    bool operator!=(const map_iterator &other) const {
      return other.ptr_ != ptr_;
    }

   private:
    ptr_t ptr_, past_ptr_;
  };

  class const_map_iterator : public map_iterator {
   public:
    using typename map_iterator::ptr_t;

    explicit const_map_iterator(ptr_t ptr) : map_iterator(ptr) {}

    const_reference operator*() const {
      return {this->ptr_->key_, this->ptr_->value_};
    }
  };

  value_t &at(const key_t &key) const {
    tree_node found_node = tree<T1, T2>::find(tree<T1, T2>::root_, key);

    if (found_node == nullptr) {
      throw std::out_of_range("out_of_range");
    }
    return found_node->value_;
  }

  value_t &operator[](const key_t &key) {
    tree_node found_node = tree<T1, T2>::find(tree<T1, T2>::root_, key);

    if (found_node == nullptr) {
      tree<T1, T2>::insert(key, value_t());
      found_node = tree<T1, T2>::find(tree<T1, T2>::root_, key);
    }
    return found_node->value_;
  }

  bool empty() const { return tree<T1, T2>::root_ == nullptr; }

  size_t size() const {
    size_t result = 0;
    for (auto it = begin(); it != end(); ++it) {
      ++result;
    }
    return result;
  }

  std::pair<iterator, bool> insert(const_reference pair) {
    bool success = false;
    tree_node tmp = tree<T1, T2>::find(tree<T1, T2>::root_, pair.first);

    if (tmp == nullptr) {
      success = true;
      tree<T1, T2>::insert(pair.first, pair.second);
      tmp = tree<T1, T2>::find(tree<T1, T2>::root_, pair.first);
    }

    return {map_iterator(tmp), success};
  }

  std::pair<iterator, bool> insert(const key_t &key, const value_t &obj) {
    return insert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_t &key,
                                             const value_t &obj) {
    auto it_result = insert({key, obj});
    if (!it_result.second) {
      it_result.first.ptr_->second =
          obj;  // обновляем значение если пара уже существует.
    }
    return it_result;
  }

  void erase(iterator pos) {
    tree<T1, T2>::remove(pos.ptr_->key_, pos.ptr_->value_);
  }

  void swap(map &other) noexcept {
    std::swap(tree<T1, T2>::root_, other.root_);
  }

  void merge(map &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
  }

  bool contains(const key_t &key) const {
    return tree<T1, T2>::find(tree<T1, T2>::root_, key) != nullptr;
  }

  iterator find(const key_t key) {
    auto tmp = tree<T1, T2>::find(tree<T1, T2>::root_, key);
    if (tmp == nullptr) {
      return end();
    }
    return iterator(tmp);
  }

  void clear() {
    delete tree<T1, T2>::root_;  // Удаление всех узлов дерева.
    tree<T1, T2>::root_ = nullptr;  // Обнуление корня.
  }

  ~map() { clear(); }  // Удаляем все при уничтожении объекта.
};
}  // namespace s21
#endif
