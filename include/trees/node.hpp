/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:56:34 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/16 19:42:56 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP_
#define NODE_HPP_

namespace ft {
typedef bool color;

#define BLACK false
#define RED true

template <class T>
struct node {
    typedef T                       value_type;
    typedef value_type             *pointer;
    typedef node<value_type>       *node_pointer;
    typedef const node<value_type> *const_node_pointer;

    node(pointer _key, node *_parent = NULL, node *_left = NULL, node *_right = NULL,
         color _col = BLACK, bool _is_leaf = false, bool _is_end = false)
        : key(_key),
          parent(_parent),
          left(_left),
          right(_right),
          color(_col),
          is_leaf(_is_leaf),
          is_end(_is_end) {}

    pointer      key;
    node_pointer parent;
    node_pointer left;
    node_pointer right;
    color        color;
    bool         is_leaf;
    bool         is_end;
};
}  // namespace ft

#endif