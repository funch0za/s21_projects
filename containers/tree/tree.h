#ifndef TREE_H
#define TREE_H

#include <sys/types.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace s21 {
template <class T1, class T2>
class tree {
 protected:
  using value_t = T1;
  using key_t = T2;

  struct node {
    key_t key_;
    value_t value_;
    node *left_;
    node *right_;
    node *parent_;
    int32_t height_;

    node() : left_(nullptr), right_(nullptr), parent_(nullptr), height_(0) {};

    node(const key_t key, const value_t value)
        : key_(key),
          value_(value),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr),
          height_(0) {};

    node(const key_t key, const value_t value, node *parent)
        : key_(key),
          value_(value),
          parent_(parent),
          left_(nullptr),
          right_(nullptr),
          height_(parent ? parent_->height_ + 1 : 0) {};

    void fix_height() {
      if (left_ == nullptr && right_ == nullptr) {
        height_ = 1;
      } else if (left_ == nullptr) {
        height_ = right_->height_ + 1;
      } else if (right_ == nullptr) {
        height_ = left_->height_ + 1;
      } else {
        height_ = std::max(left_->height_, right_->height_) + 1;
      }
    }

    int32_t balance_factor() const {
      if (left_ == nullptr && right_ == nullptr) {
        return 0;
      }
      return (left_ ? left_->height_ : 0) - (right_ ? right_->height_ : 0);
    }

    ~node() {
      delete left_;
      delete right_;
    }

    friend class tree;
  };

  tree() : root_(nullptr) {}

 private:
  node *rotate_left(node *cur) {
    node *cur_right = cur->right_;

    cur->right_ = cur_right->left_;
    cur_right->left_ = cur;

    cur->fix_height();
    cur_right->fix_height();

    return cur_right;
  }

  node *rotate_right(node *cur) {
    if (cur->left_ == nullptr) {
      return cur;
    }
    node *cur_left = cur->left_;
    cur->left_ = cur_left->right_;
    cur_left->right_ = cur;

    cur->fix_height();
    cur_left->fix_height();

    return cur_left;
  }

  node *balance(node *cur) {
    if (cur == nullptr) {
      return nullptr;
    }

    cur->fix_height();

    if (cur->balance_factor() == 2) {
      if (cur->right_->balance_factor() < 0) {
        cur->right_ = rotate_right(cur->right_);
      }
      return rotate_left(cur);
    }

    if (cur->balance_factor() == -2) {
      if (cur->left_->balance_factor() > 0) {
        cur->left_ = rotate_left(cur->left_);
      }
      return rotate_right(cur);
    }

    return cur;
  }

 protected:
  node *root_;

  ~tree() { delete root_; };

  node *insert(node *cur, node *from, const key_t key, const value_t value) {
    if (cur == nullptr) {
      return new node(key, value, from);
    }

    if (key == cur->key_) {
      cur->value_ = value;
    } else if (key < cur->key_) {
      cur->left_ = insert(cur->left_, cur, key, value);
    } else {
      cur->right_ = insert(cur->right_, cur, key, value);
    }

    return balance(cur);
  }

  node *remove(node *cur, const key_t key, const value_t value) {
    if (cur == nullptr) {
      return nullptr;
    }

    if (key == cur->key_) {
      node *left = cur->left_;
      node *right = cur->right_;

      delete cur;

      if (left == nullptr) {
        return right;
      }
      if (right == nullptr) {
        return left;
      }

      node *subtree_min = find_min(right);
      subtree_min->right_ = remove_min(right);
      subtree_min->left_ = left;
      return balance(subtree_min);

    } else if (key < cur->key_) {
      cur->left_ = remove(cur->left_, key, value);
    } else {
      cur->right_ = remove(cur->right_, key, value);
    }

    return balance(cur);
  }

  node *find_min(node *cur) const {
    while (cur && cur->left_) {
      cur = cur->left_;
    }
    return cur;
  }

  node *remove_min(node *cur) {
    if (cur == nullptr || cur->left_ == nullptr) {
      return cur ? cur->right_ : nullptr;
    }
    cur->left_ = remove_min(cur->left_);
    return balance(cur);
  }

  node *find(node *cur, const key_t key) const {
    if (cur == nullptr || cur->key_ == key) {
      return cur;
    }

    if (key < cur->key_) {
      return find(cur->left_, key);
    }

    return find(cur->right_, key);
  }

 public:
  void insert(const key_t key, const value_t value) {
    root_ = insert(root_, nullptr, key, value);
  }

  void remove(const key_t key, const value_t value) {
    root_ = remove(root_, key, value);
  }
};
}  // namespace s21

#endif
