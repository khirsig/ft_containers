/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/09 09:20:16 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_ITERATOR_HPP_
#define RED_BLACK_TREE_ITERATOR_HPP_

#include "type_traits.hpp"

namespace ft {

template <class T>
struct node;
template <class T>
node<T>* red_black_tree_min(node<T>* n);
template <class T>
node<T>* red_black_tree_max(node<T>* n);

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
        const_reference bigger_node_key =
            std::max(ft::red_black_tree_max(_ptr->right)->key, _ptr->parent->key);
        if (bigger_node_key == _ptr->right->key)
            _ptr = _ptr->right;
        else
            _ptr = _ptr->parent;
        return (*this);
    }

    tree_iterator& operator--() {
        if (std::min(ft::red_black_tree_min(_ptr->left), _ptr->parent->key) == _ptr->left->key)
            _ptr = _ptr->left;
        else
            _ptr = _ptr->parent;
        return (*this);
    }

    node_ptr operator->() { return (_ptr); }

    reference operator*() { return (_ptr->key); }

   private:
    node_ptr _ptr;
};
}  // namespace ft

#endif
