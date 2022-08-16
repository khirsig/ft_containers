/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/16 12:51:18 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_CONST_TREE_ITERATOR_HPP_
#define RED_BLACK_CONST_TREE_ITERATOR_HPP_

#include "type_traits.hpp"

namespace ft {

template <class T>
struct node;
template <class T>
node<T>* tree_min(node<T>* x);
template <class T>
node<T>* tree_max(node<T>* x);

template <class T, class Val>
class const_tree_iterator {
   public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T                              node_ptr;
    typedef std::ptrdiff_t                 difference_type;
    typedef Val                            value_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;

    const_tree_iterator(const node_ptr& ptr = NULL) : _ptr(ptr) {}

    const_tree_iterator(const const_tree_iterator& other) : _ptr(other._ptr) {}

    ~const_tree_iterator() {}

    node_ptr base() const { return (_ptr); }

    const_tree_iterator& operator=(const const_tree_iterator& other) {
        if (*this != other) {
            _ptr = other._ptr;
        }
        return (*this);
    }

    const_tree_iterator& operator++() {
        _ptr = _tree_next_iter(_ptr);
        return (*this);
    }

    const_tree_iterator operator++(int) {
        const_tree_iterator tmp(*this);
        ++(*this);
        return (tmp);
    }

    const_tree_iterator& operator--() {
        _ptr = _tree_prev_iter(_ptr);
        return (*this);
    }

    const_tree_iterator operator--(int) {
        const_tree_iterator tmp(*this);
        --(*this);
        return (tmp);
    }

    pointer operator->() const { return (_ptr->key); }

    reference operator*() const { return (*_ptr->key); }

    template <class U, class V>
    friend bool operator==(const_tree_iterator<U, V>& x, const_tree_iterator<U, V>& y);

    template <class U, class V>
    friend bool operator!=(const_tree_iterator<U, V>& x, const_tree_iterator<U, V>& y);

   private:
    const node_pointer* _ptr;

    bool _tree_is_left_child(node_ptr x) { return (x == x->parent->left); }

    node_ptr _tree_next_iter(node_ptr x) {
        if (!x->right->is_leaf)
            return (tree_min(x->right));
        if (x->right->is_end)
            return (x->right);
        while (!_tree_is_left_child(x))
            x = x->parent;

        return (x->parent);
    }

    node_ptr _tree_prev_iter(node_ptr x) {
        if (!x->left->is_leaf)
            return (tree_max(x->left));
        if (x->left->is_end)
            return (x->left);
        node_ptr xx = static_cast<node_ptr>(x);
        while (_tree_is_left_child(xx))
            xx = xx->parent;

        return (xx->parent);
    }
};

template <class T, class Val>
bool operator==(const_tree_iterator<T, Val>& x, const_tree_iterator<T, Val>& y) {
    return (x._ptr == y._ptr);
}

template <class T, class Val>
bool operator!=(const_tree_iterator<T, Val>& x, const_tree_iterator<T, Val>& y) {
    return !(x._ptr == y._ptr);
}
}  // namespace ft

#endif
