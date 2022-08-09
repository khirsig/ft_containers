/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/09 15:37:47 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "../iterators/tree_iterator.hpp"
#include "../utils/pair.hpp"
#include "algorithm"
#include "binary_search_tree.hpp"

namespace ft {
template <class T, class Compare = std::less<T>, class Allocator = std::allocator<ft::node<T> > >
class red_black_tree {
   public:
    typedef T                                        value_type;
    typedef Allocator                                allocator_type;
    typedef value_type                              &reference;
    typedef value_type                              *pointer;
    typedef ft::node<value_type>                     node;
    typedef node                                    *node_pointer;
    typedef node                                    &node_reference;
    typedef ft::tree_iterator<node_pointer, T>       iterator;
    typedef ft::tree_iterator<node_pointer, T>       const_iterator;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type       size_type;
    typedef Compare                                  compare_type;

    red_black_tree(allocator_type alloc = allocator_type(), node_pointer n = NULL)
        : _root(n), _null(new node(ft::make_pair(0, 0), NULL, NULL, NULL, BLACK, true)) {
        _alloc = alloc;
        if (_root == NULL)
            _root = _null;
        _left_most = _root;
        _right_most = _root;
    }

    red_black_tree(const red_black_tree &other)
        : _null(new node(0, NULL, NULL, NULL, BLACK, true)) {
        _root = _null;
        _left_most = _root;
        _right_most = _root;
        _clone_tree(other);
    }

    ~red_black_tree() {
        clear();
        delete (_null);
    }

    void print() { print(_root); }

    void print(const node_pointer n) { print(n, "", false); }

    void print(const node_pointer n, const std::string &prefix, bool isLeft) {
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
            if (n != _null)
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

    iterator begin() { return (_left_most); }

    const_iterator begin() const { return (_left_most); }

    iterator end() { return (_right_most); }

    const_iterator end() const { return (_right_most); }

    bool empty() const { return (_root == _null ? true : false); }

    size_type size() const { return (_size); }

    size_type max_size() const { return (_alloc.max_size()); }

    node_pointer search(node_pointer n, T key) {
        if (n == _null || n->key == key)
            return (n);
        if (key < n->key)
            return (search(n->left, key));
        else
            return (search(n->right, key));
    }

    node_pointer iterative_search(node_pointer n, T key) {
        while (n != _null && key != n->key) {
            if (key < n->key)
                n = n->left;
            else
                n = n->right;
        }
        return (n);
    }

    void left_rotate(node_pointer x) {
        node_pointer y = x->right;
        x->right = y->left;
        if (y->left != _null)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == _null)
            _root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(node_pointer x) {
        node_pointer y = x->left;
        x->left = y->right;
        if (y->right != _null)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == _null)
            _root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    ft::pair<iterator, bool> insert(value_type &val) {
        if (_root->key == val)
            return (ft::make_pair(_root, false));
        node_pointer needle = search(_root, val);
        if (needle != _root)
            return (ft::make_pair(needle, false));
        node_pointer input = _create_node(val);
        node_pointer n = _null;
        node_pointer r = _root;
        while (r != _null) {
            n = r;
            if (input->key < r->key)
                r = r->left;
            else
                r = r->right;
        }
        input->parent = n;
        if (n == _null)
            _root = input;
        else if (input->key < n->key)
            n->left = input;
        else
            n->right = input;
        input->left = _null;
        input->right = _null;
        input->color = RED;
        if (_left_most->left == input || input == _root)
            _left_most = input;
        if (_right_most->right == input || input == _root)
            _right_most = input;
        _insert_fixup(input);
        return (ft::make_pair(input, true));
    }

    void transplant(node_pointer target, node_pointer input) {
        if (target->parent == _null)
            _root = input;
        else if (target == target->parent->left)
            target->parent->left = input;
        else
            target->parent->right = input;
        input->parent = target->parent;
    }

    void destroy(node_pointer input) {
        node_pointer y = input;
        node_pointer x;
        color        y_original_color = y->color;
        if (input->left == _null) {
            x = input->right;
            transplant(input, input->right);
        } else if (input->right == _null) {
            x = input->left;
            transplant(input, input->left);
        } else {
            y = begin();
            y_original_color = y->color;
            x = y->right;
            if (y->parent == input)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = input->right;
                y->right->parent = y;
            }
            transplant(input, y);
            y->left = input->left;
            y->left->parent = y;
            y->color = input->color;
        }
        if (y_original_color == BLACK)
            _destroy_fixup(x);
        _destroy_node(input);
    }

    void clear() {
        iterator it = begin();
        while (it.base() != end().base()) {
            _destroy_node(it++.base());
        }
        _destroy_node(end().base());
        _left_most = _null;
        _right_most = _null;
        _root = _null;
    };

    void swap(red_black_tree &other) {
        if (this != &other) {
            node_pointer   tmp_root = other._root;
            node_pointer   tmp_null = other._null;
            node_pointer   tmp_left_most = other._left_most;
            node_pointer   tmp_right_most = other._right_most;
            allocator_type tmp_alloc = other._alloc;

            other._root = _root;
            other._null = _null;
            other._left_most = _left_most;
            other._right_most = _right_most;
            other._alloc = _alloc;
            _root = tmp_root;
            _null = tmp_null;
            _left_most = tmp_left_most;
            _right_most = tmp_right_most;
            _alloc = tmp_alloc;
        }
    }

   private:
    node_pointer   _root;
    node_pointer   _null;
    node_pointer   _left_most;
    node_pointer   _right_most;
    allocator_type _alloc;
    size_type      _size;

    node_pointer _create_node(value_type &val) {
        node_pointer n = _alloc.allocate(1);
        _alloc.construct(n, node(val, NULL, NULL, NULL));
        _size++;

        return (n);
    }

    void _destroy_node(node_pointer n) {
        _alloc.destroy(n);
        _alloc.deallocate(n, 1);
        _size--;
    }

    void _clone_tree(const red_black_tree &other) {
        for (iterator it = other.begin(); it != other.end(); ++it)
            insert(*it);
    }

    void _destroy_fixup(node_pointer x) {
        while (x != _root && x->color == BLACK) {
            if (x == x->parent->left) {
                node_pointer w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = _root;
                }
            } else {
                node_pointer w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = _root;
                }
            }
        }
        x->color = BLACK;
    }

    void _insert_fixup(node_pointer input) {
        while (input->parent->color == RED) {
            if (input->parent == input->parent->parent->left) {
                node_pointer n = input->parent->parent->right;
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
                node_pointer n = input->parent->parent->left;
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
};

template <class T>
node<T> *tree_min(node<T> *x) {
    while (!x->left->is_leaf)
        x = x->left;
    return (x);
}
template <class T>
node<T> *tree_max(node<T> *x) {
    while (!x->right->is_leaf)
        x = x->right;
    return (x);
}

}  // namespace ft

#endif