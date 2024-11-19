#ifndef TREE_H
#define TREE_H

#include <sys/types.h>
#include <algorithm>
#include <cstdint>
#include <utility>

namespace s21 {

template <class T1, class T2>
class tree {
 public:
  using value_t = T1;
  using key_t = T2;
  using pair = std::pair<key_t, value_t>;
  using reference = value_t &;
  using const_reference = const value_t &;

  class iterator {
    iterator();
    reference operator*() const;
    iterator operator++(int);
    iterator operator--(int);
    
    friend class tree;
  };

  class const_iterator {};

 protected:
  struct node {
    key_t key_;
    value_t value_;
    int32_t height_;
    node *left_, *right_, *parent_;

    node();
    node(const key_t key, const value_t value);
    node(const key_t key, const value_t value, node *parent);
    void fix_height();
    int32_t balance_factor() const;
      
    ~node();

    friend class tree;
  };

 private:
  node *root_;

  node *insert(node *cur, const key_t key, const value_t value);
  node *balance(node *cur);
  node *rotate_left(node *cur);
  node *rotate_right(node *cur);

  node *find_min(node *cur);

 public:
  void insert(const key_t key, const value_t value);
};
}  // namespace s21

#include "tree.tpp"

#endif
