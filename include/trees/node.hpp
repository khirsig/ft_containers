/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 08:56:34 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/10 08:58:12 by khirsig          ###   ########.fr       */
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
    typedef T value_type;

    node(T _key, node *_parent = NULL, node *_left = NULL, node *_right = NULL, color _col = BLACK,
         bool _is_leaf = false)
        : key(_key), parent(_parent), left(_left), right(_right), color(_col), is_leaf(_is_leaf) {}

    T     key;
    node *parent;
    node *left;
    node *right;
    color color;
    bool  is_leaf;
};
}  // namespace ft

#endif