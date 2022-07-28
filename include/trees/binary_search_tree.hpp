/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:58:18 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 13:09:32 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <string>

#define BLACK false
#define RED true

namespace ft {
	typedef bool	color;

	template <class T>
		struct node {
			node(T _key, node *_parent = NULL, node *_left = NULL, node *_right = NULL, color _col = BLACK)
				: key(_key),
				  parent(_parent),
				  left(_left),
				  right(_right),
				  color(_col) { }

			T		key;
			node	*parent;
			node	*left;
			node	*right;
			color	color;
		};

	template <class T>
		class binary_search_tree {
			public:
				binary_search_tree(node<T> *root = NULL)
					: _root(root) { }

				node<T>	*root() const
				{
					return (_root);
				}

				void	print(const node<T> *n)
				{
					print(n, "", false);
				}

				void	print(const node<T> *n, const std::string &prefix, bool isLeft)
				{
					if (n != NULL)
					{
						std::cout << prefix;

						if (isLeft)
							std::cout << "├──";
						else
							std::cout << "└──";

						std::cout << n->key << "\n";

						if (isLeft)
						{
							print(n->left, prefix + "│   ", true);
							print(n->right, prefix + "│   ", false);
						}
						else
						{
							print(n->left, prefix + "    ", true);
							print(n->right, prefix + "    ", false);
						}
					}
				}

				node<T>	*search(node<T> *n, T key)
				{
					if (n == NULL || n->key == key)
						return (n);
					if (key < n->key)
						return (search(n->left, key));
					else
						return (search(n->right, key));
				}

				node<T> *iterative_search(node<T> *n, T key)
				{
					while (n != NULL && key != n->key)
					{
						if (key < n->key)
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

				void insert(binary_search_tree &tree, node<T> *input)
				{
					node<T> *n = NULL;
					node<T> *r = tree._root;
					while (r != NULL)
					{
						n = r;
						if (input->key < r->key)
							r = r->left;
						else
							r = r->right;
					}
					input->parent = n;
					if (n == NULL)
						tree._root = input;
					else if (input->key < n->key)
						n->left = input;
					else
						n->right = input;
				}

			private:
				node<T>	*_root;
		};
}

#endif