/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:58:18 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 11:29:50 by khirsig          ###   ########.fr       */
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

	template <class T>
		class binary_search_tree {
			public:

				void	inorder_tree_walk(node *n)
				{
					if (n != NULL)
					{
						inorder_tree_walk(n->left);
						std::cout << n->value << "\n";
						inorder_tree_walk(n->right);
					}
				}

				node<T>	*tree_search(node *n, T key)
				{
					if (n == NULL || n->value == key)
						return (n);
					if (key < n->value)
						return (tree_search(n->left, key));
					else
						return (tree_search(n->right, key));
				}

				node<T> *iterative_tree_search(node *n, T key)
				{
					while (n != NULL && key != n->value)
					{
						if (key < n->value)
							n = n->left;
						else
							n = n->right;
					}
					return (n);
				}
			private:
				node<T>	*_node;
		}
}

#endif