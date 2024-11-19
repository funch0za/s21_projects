#include <cstdint>
#include <sys/types.h>

namespace s21 {
template <class T1, class T2>
tree<T1, T2>::node::node() :left_(nullptr), right_(nullptr), parent_(nullptr), height_(0){
}

template <class T1, class T2>
tree<T1, T2>::node::node(const key_t key, const value_t value) : node() {
  key_ = key;
  value_ = value;
}

template <class T1, class T2>
tree<T1, T2>::node::node(const key_t key, const value_t value, tree::node *parent)
    : node(key, value) {
  parent_ = parent;
  height_ = parent->height_ + 1;
}

template<class T1, class T2>
void tree<T1, T2>::node::fix_height() {
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

template<class T1, class T2>
int32_t tree<T1, T2>::node::balance_factor() const {
  if (left_ == nullptr && right_ == nullptr) {
    return 0;
  }
  if (left_ == nullptr) {
    return 0 - right_->height_;
  }
  if (right_ == nullptr) {
    return left_->height_;
  }
  return left_->height_ - right_->height_;
}

template <class T1, class T2>
tree<T1, T2>::node::~node() = default;

template <class T1, class T2>
typename tree<T1, T2>::node* tree<T1, T2>::rotate_left(typename tree<T1, T2>::node *cur) {
  typename tree<T1, T2>::node *cur_right = cur->right_;
  
  cur->right_ = cur_right->left_;
  cur_right->left_ = cur;
  
  cur->fix_height();
  cur_right->fix_height();

  return cur_right;
}

template <class T1, class T2>
typename tree<T1, T2>::node* tree<T1, T2>::rotate_right(typename tree<T1, T2>::node *cur) {
  typename tree<T1, T2>::node *cur_left = cur->left_;
  
  cur->left_ = cur_left->left_;
  cur_left->right_ = cur;
  
  cur->fix_height();
  cur_left->fix_height();

  return cur_left;
}

template <class T1, class T2>
typename tree<T1, T2>::node* tree<T1, T2>::balance(typename tree<T1, T2>::node *cur) {
  cur->fix_height();
  
  if (cur->balance_factor() == -2) {
    if (cur->left_->balance_factor() == 0 ||
        cur->left_->balance_factor() == -1) {
      return rotate_left(cur);
    }
    cur->right_ = rotate_right(cur->right_);
    return rotate_left(cur);
  } else if (cur->balance_factor() == 2) {
    if (cur->right_->balance_factor() == 0 ||
        cur->right_->balance_factor() == 1) {
      return rotate_right(cur);
    }
    cur->left_ = rotate_left(cur->left_);
    return rotate_right(cur);
  }

  return cur;
}

template<class T1, class T2>
typename tree<T1, T2>::node* tree<T1, T2>::insert(typename tree<T1, T2>::node *cur, const key_t key, const value_t value) {
  if (cur == nullptr) {
    return new typename tree<T1, T2>::node(key, value);
  }
  
  if (key == cur->key_) {
    cur->value_ = value;
  } else if (key < cur->key_) {
    cur->left_ = insert(cur->left_, key, value);
  } else {
    cur->right_ = insert(cur->right_, key, value);
  }

  return balance(cur);
}

template<class T1, class T2>
void tree<T1, T2>::insert(const key_t key, const value_t value) { 
  root_ = insert(root_, key, value);
}

}  // namespace s21
