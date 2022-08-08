/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:24:57 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/08 15:59:42 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_ITERATOR_HPP_
#define RED_BLACK_TREE_ITERATOR_HPP_

#include "../trees/red_black_tree.hpp"
#include "type_traits.hpp"

namespace ft {
template <class T>
class tree_iterator {
   public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T                              value_type;
    typedef std::ptrdiff_t                 difference_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;

    tree_iterator(pointer ptr = NULL) : _ptr(ptr) {}

    ~tree_iterator() {}

    pointer base() const { return (_ptr); }

    tree_iterator& operator++() {
        _ptr = ft::min(_ptr.right);
        return (*this);
    }

    tree_iterator& operator--() {
        _ptr = ft::max(_ptr.left);
        return (*this);
    }

    pointer operator->() { return (_ptr); }

    reference operator*() { return (*_ptr); }

   private:
    pointer _ptr;
};
}  // namespace ft

#endif