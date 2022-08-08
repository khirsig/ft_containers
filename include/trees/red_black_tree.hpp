/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/08 11:06:25 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "binary_search_tree.hpp"

namespace ft {
template <class T>
class red_black_tree {
   public:
    red_black_tree(node<T> *n = NULL) : _root(n), _null(node<T>(0, NULL, NULL, NULL, BLACK)) {
        if (_root == NULL) _root = &_null;
        _left_most = _root;
        _right_most = _root;
    }

    void print() { print(_root); }

    void print(const node<T> *n) { print(n, "", false); }

    void print(const node<T> *n, const std::string &prefix, bool isLeft) {
        if (n != NULL) {
            std::cout << prefix;
            if (isLeft)
                std::cout << "├──";
            else
                std::cout << "└──";
            if (n == _left_most)
                std::cout << "\033[32m";
            else if (n == _right_most)
                std::cout << "\033[33m";
            else if (n->color == RED)
                std::cout << "\033[31m";
            else
                std::cout << "\033[30m";
            if (n != &_null)
                std::cout << n->key << "\033[37m\n";
            else
                std::cout << "null\033[37m\n";
            if (isLeft) {
                print(n->left, prefix + "│   ", true);
                print(n->right, prefix + "│   ", false);
            } else {
                print(n->left, prefix + "    ", true);
                print(n->right, prefix + "    ", false);
            }
        }
    }

    node<T> *min() { return (_left_most); }

    node<T> *min(node<T> *n) {
        while (n->left != NULL) n = n->left;
        return (n);
    }

    node<T> *max() { return (_right_most); }

    node<T> *max(node<T> *n) {
        while (n->right != NULL) n = n->right;
        return (n);
    }

    void left_rotate(node<T> *x) {
        node<T> *y = x->right;
        x->right = y->left;
        if (y->left != &_null) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == &_null)
            _root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(node<T> *x) {
        node<T> *y = x->left;
        x->left = y->right;
        if (y->right != &_null) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == &_null)
            _root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insert(node<T> *input) {
        node<T> *n = &_null;
        node<T> *r = _root;
        while (r != &_null) {
            n = r;
            if (input->key < r->key)
                r = r->left;
            else
                r = r->right;
        }
        input->parent = n;
        if (n == &_null)
            _root = input;
        else if (input->key < n->key)
            n->left = input;
        else
            n->right = input;
        input->left = &_null;
        input->right = &_null;
        input->color = RED;
        if (_left_most->left == input || input == _root) _left_most = input;
        if (_right_most->right == input || input == _root) _right_most = input;
        insert_fixup(input);
    }

    void insert_fixup(node<T> *input) {
        while (input->parent->color == RED) {
            if (input->parent == input->parent->parent->left) {
                node<T> *n = input->parent->parent->right;
                if (n->color == RED) {
                    input->parent->color = BLACK;
                    n->color = BLACK;
                    input->parent->parent->color = RED;
                    input = input->parent->parent;
                } else {
                    if (input == input->parent->right) {
                        input = input->parent;
                        left_rotate(input);
                    }
                    input->parent->color = BLACK;
                    input->parent->parent->color = RED;
                    right_rotate(input->parent->parent);
                }
            } else {
                node<T> *n = input->parent->parent->left;
                if (n->color == RED) {
                    input->parent->color = BLACK;
                    n->color = BLACK;
                    input->parent->parent->color = RED;
                    input = input->parent->parent;
                } else {
                    if (input == input->parent->left) {
                        input = input->parent;
                        right_rotate(input);
                    }
                    input->parent->color = BLACK;
                    input->parent->parent->color = RED;
                    left_rotate(input->parent->parent);
                }
            }
        }
        _root->color = BLACK;
    }

    void transplant(node<T> *target, node<T> *input) {
        if (target->parent == _null)
            _root = input;
        else if (target == target->parent->left)
            target->parent->left = input;
        else
            target->parent->right = input;
        input->parent = target->parent;
    }

    // void	destroy(node<T> *input)
    // {
    // 	node<T> *y = input;
    // 	node<T> *x;
    // 	color yCol = y->color;
    // 	if (input->left == _null)
    // 	{
    // 		x = input->right;
    // 		transplant(input, input->right);
    // 	}
    // 	else if (input->right == _null)
    // 	{
    // 		x = input->left;
    // 		transplant(input, input->left);
    // 	}
    // 	else
    // 	{
    // 		y = minimum
    // 	}
    // }
   private:
    node<T> *_root;
    node<T> _null;
    node<T> *_left_most;
    node<T> *_right_most;
};
}  // namespace ft

#endif