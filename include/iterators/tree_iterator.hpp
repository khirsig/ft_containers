/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/09 10:06:40 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_ITERATOR_HPP_
#define RED_BLACK_TREE_ITERATOR_HPP_

#include "type_traits.hpp"

namespace ft {

template <class T>
struct node;
template <class T>
node<T>* tree_min(node<T>* x);
template <class T>
node<T>* tree_max(node<T>* x);

template <class T, class Val>
class tree_iterator {
   public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T                              node_ptr;
    typedef std::ptrdiff_t                 difference_type;
    typedef Val                            value_type;
    typedef value_type&                    reference;
    typedef const value_type&              const_reference;
    typedef value_type*                    pointer;

    tree_iterator(node_ptr ptr = NULL) : _ptr(ptr) {}

    ~tree_iterator() {}

    pointer base() const { return (_ptr->key); }

    tree_iterator& operator++() {
        _ptr = _tree_next_iter(_ptr);
        return (*this);
    }

    tree_iterator& operator--() {
        _ptr = _tree_prev_iter(_ptr);
        return (*this);
    }

    node_ptr operator->() { return (_ptr); }

    reference operator*() { return (_ptr->key); }

   private:
    node_ptr _ptr;

    bool _tree_is_left_child(node_ptr x) { return (x == x->parent->left); }

    node_ptr _tree_next_iter(node_ptr x) {
        if (!x->right->is_leaf)
            return (tree_min(x->right));
        while (!_tree_is_left_child(x))
            x = x->parent;

        return (x->parent);
    }

    node_ptr _tree_prev_iter(node_ptr x) {
        if (!x->left->is_leaf)
            return (tree_max(x->left));
        node_ptr xx = static_cast<node_ptr>(x);
        while (_tree_is_left_child(xx))
            xx = xx->parent;

        return (xx->parent);
    }
};
}  // namespace ft

#endif