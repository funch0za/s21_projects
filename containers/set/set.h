#ifndef SET_H
#define SET_H

#include "../tree/tree.h"

namespace s21 {
template <class T>
class set : public tree<T, T> {
 public:
  class set_iterator;
  class const_set_iterator;

  using key_t = T;
  using value_t = T;
  using reference = value_t &;
  using const_reference = const value_t &;
  using iterator = set_iterator;
  using const_iterator = const_set_iterator;
  using size_t = std::size_t;
  using tree_node = typename tree<T, T>::node *;

  set() : tree<T, T>() {}

  set(std::initializer_list<value_t> const &items) {
    for (const auto &elem : items) {
      tree<T, T>::insert(elem, elem);
    }
  }

  set(const set &s) {
    auto it = s.begin();
    while (it != s.end()) {
      value_t elem = *it;
      tree<T, T>::insert(elem, elem);
      ++it;
    }
  }

  set(set &&s) noexcept {
    if (this != &s) {
      tree<T, T>::root_ = s.root_;
      s.root_ = nullptr;
    }
  }

  set &operator=(set &&s) noexcept {
    if (this != &s) {
      clear();
      tree<T, T>::root_ = s.root_;
      s.root_ = nullptr;
    }
    return *this;
  }

 private:
  static tree_node next(tree_node cur) {
    if (cur == nullptr) return nullptr;

    if (cur->right_ != nullptr) {
      return tree<T, T>::find_min(cur->right_);
    }

    tree_node parent = cur->parent_;
    while (parent != nullptr && cur == parent->right_) {
      cur = parent;
      parent = parent->parent_;
    }

    return parent;
  }

  static tree_node prev(tree_node cur) {
    if (cur == nullptr) return nullptr;

    if (cur->left_ != nullptr) {
      return find_max(cur->left_);
    }

    tree_node parent = cur->parent_;
    while (parent != nullptr && cur == parent->left_) {
      cur = parent;
      parent = parent->parent_;
    }

    return parent;
  }

 public:
  iterator begin() const {
    return set_iterator(tree<T, T>::find_min(tree<T, T>::root_));
  }

  iterator end() const { return set_iterator(nullptr); }

  class set_iterator {
   public:
    friend class set;

    using ptr_t = tree_node;

    explicit set_iterator(ptr_t ptr) : ptr_(ptr) {}

    reference operator*() const { return ptr_->key_; }

    set_iterator &operator++(int) {
      set_iterator tmp(*this);
      ptr_ = next(ptr_);
      return tmp;
    }

    set_iterator &operator++() {
      ptr_ = next(ptr_);
      return *this;
    }

    set_iterator &operator--(int) {
      set_iterator tmp(*this);
      ptr_ = prev(ptr_);
      return tmp;
    }

    set_iterator &operator--() {
      ptr_ = prev(ptr_);
      return *this;
    }

    bool operator==(const set_iterator &other) const {
      return other.ptr_ == ptr_;
    }

    bool operator!=(const set_iterator &other) const {
      return other.ptr_ != ptr_;
    }

   private:
    ptr_t ptr_;
  };

  class const_set_iterator : public set_iterator {
   public:
    using typename set_iterator::ptr_t;

    const_set_iterator(ptr_t ptr) : set_iterator(ptr) {}

    const_reference operator*() const { return this->ptr_->key_; }
  };

  std::pair<iterator, bool> insert(const_reference value) {
    bool success = false;
    tree_node tmp = tree<T, T>::find(tree<T, T>::root_, value);
    if (tmp == nullptr) {
      success = true;
      tree<T, T>::insert(value, value);
      tmp = tree<T, T>::find(tree<T, T>::root_, value);
    }
    return {iterator(tmp), success};
  }

  void erase(iterator pos) {
    tree<T, T>::remove(pos.ptr_->key_, pos.ptr_->key_);
  }

  void swap(set &other) noexcept { std::swap(tree<T, T>::root_, other.root_); }

  void merge(set &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
  }

  bool contains(const key_t &key) const {
    return tree<T, T>::find(tree<T, T>::root_, key) != nullptr;
  }

  iterator find(const key_t key) {
    tree_node tmp = tree<T, T>::find(tree<T, T>::root_, key);
    if (tmp == nullptr) {
      return end();
    }
    return iterator(tmp);
  }

  size_t size() const {
    size_t result = 0;
    for (auto it = begin(); it != end(); ++it) {
      ++result;
    }
    return result;
  }

  bool empty() const { return tree<T, T>::root_ == nullptr; }

  void clear() {
    delete root_;     // Удаление всех узлов дерева
    root_ = nullptr;  // Обнуление корня
  }

  ~set() { clear(); }  // Удаляем все при уничтожении объекта.
};

}  // namespace s21

#endif
