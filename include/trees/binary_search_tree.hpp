/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:58:18 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 12:27:01 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include <iostream>

#define BLACK false
#define RED true

namespace ft {
	typedef bool	color;

	template <class T>
		struct node {
			node(T val, node *prnt = NULL, node *lft = NULL, node *rgt = NULL, color col = BLACK)
				: value(val),
				  parent(prnt),
				  left(lft),
				  right(rgt),
				  color(col) { }

			T		value;
			node	*left;
			node	*right;
			node	*parent;
			color	color;
		};

	template <class T>
		class binary_search_tree {
			public:

				void	inorder_walk(node<T> *n)
				{
					if (n != NULL)
					{
						inorder_walk(n->left);
						std::cout << n->value << "\n";
						inorder_walk(n->right);
					}
				}

				node<T>	*search(node<T> *n, T key)
				{
					if (n == NULL || n->value == key)
						return (n);
					if (key < n->value)
						return (search(n->left, key));
					else
						return (search(n->right, key));
				}

				node<T> *iterative_search(node<T> *n, T key)
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

				node<T> *min(node<T> *n)
				{
					while (n->left != NULL)
						n = n->left;
					return (n);
				}

				node<T> *max(node<T> *n)
				{
					while (n->right != NULL)
						n = n->right;
					return (n);
				}

				node<T>	successor(node<T> *n)
				{
					if (n->right != NULL)
						return (min(n->right));
					node<T> *p = n->parent;
					while (p != NULL && n == p->right)
					{
						n = p;
						p = p->parent;
					}
				}

			private:
				node<T>	*_root;
		};
}

#endif