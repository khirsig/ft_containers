/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:58:18 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 11:10:50 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include <iostream>

#define BLACK false
#define RED true

namespace ft {
	template <class T>
		struct node {
			node(T val, node *prnt, node *lft, node *rgt, color col = BLACK)
				: value(val),
				  parent(prnt),
				  left(lft),
				  right(rgt),
				  col(col) { }

			T		value;
			node	*left = NULL;
			node	*right = NULL;
			node	*parent = NULL;
			bool	color = BLACK;
		};

	template <

}

#endif