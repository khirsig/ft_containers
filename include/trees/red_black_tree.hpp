/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 14:42:19 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "binary_search_tree.hpp"

namespace ft {
	template <class T>
		class black_red_tree : public binary_search_tree {

			void	print(const node<T> *n, const std::string &prefix, bool isLeft)
			{
				if (n != NULL)
				{
					std::cout << prefix;
					if (isLeft)
						std::cout << "├──";
					else
						std::cout << "└──";
					if (n->color == RED)
						std::cout << "\u001b[30m";
					else
						std::cout << "\u001b[31m";
					std::cout << n->key << "\u001b[37m\n";
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
			void	left_rotate(node<T> *x)
			{
				node<T> *y = x->right;
				x->right = y->left;
				if (y->left != NULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x.parent == NULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	right_rotate(node<T> *x)
			{
				node<T> *y = x->left;
				x->left = y->right;
				if (y->right != NULL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x.parent == NULL)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void	insert(node<T> *input)
			{
				node<T> *n = NULL;
				node<T> *r = _root;
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
					_root = input;
				else if (input->key < n->key)
					n->left = input;
				else
					n->right = input;
				input->left = NULL;
				input->right = NULL;
				input->color = RED;
				insert_fixup(input);
			}

			void	insert_fixup(node<T> *input)
			{
				while (input->parent->color == RED)
				{
					if (input->parent == input->parent->parent->left)
					{
						node<T> *n = input->parent->parent->right;
						if (n->color == RED)
						{
							input->parent->color = BLACK;
							n->color = BLACK;
							input->parent->parent->color = RED;
							input = input->parent->parent;
						}
						else if (input == input->parent->right)
						{
							input = input->parent;
							left_rotate(input);
						}
						input->parent->color = BLACK;
						input->parent->parent->color = RED;
						right_rotate(input->parent->parent);
					}
					else
					{
						node<T> *n = input->parent->parent->left;
						if (n->color == RED)
						{
							input->parent->color = BLACK;
							n->color = BLACK;
							input->parent->parent->color = RED;
							input = input->parent->parent;
						}
						else if (input == input->parent->left)
						{
							input = input->parent;
							right_rotate(input);
						}
						input->parent->color = BLACK;
						input->parent->parent->color = RED;
						left_rotate(input->parent->parent);
					}
				}
				_root->color = BLACK;
			}
		};
}

#endif