/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/11 15:52:51 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "../iterators/tree_iterator.hpp"
#include "../utils/pair.hpp"
#include "./node.hpp"
#include "algorithm"
#include "functional"

namespace ft {

template <class Key, class T, class Compare, class Alloc>
class red_black_tree {
   public:
    typedef Key                                            key_type;
    typedef T                                              mapped_type;
    typedef ft::pair<const key_type, mapped_type>          value_type;
    typedef Compare                                        key_compare;
    typedef Alloc                                          allocator_type_value;
    typedef typename allocator_type_value::reference       reference;
    typedef typename allocator_type_value::const_reference const_reference;
    typedef typename allocator_type_value::pointer         pointer;
    typedef typename allocator_type_value::const_pointer   const_pointer;
    typedef ft::node<value_type>                           node;
    typedef std::allocator<node>                           allocator_type_node;
    typedef typename allocator_type_node::pointer          node_pointer;
    typedef typename allocator_type_node::reference        node_reference;
    typedef ft::tree_iterator<node_pointer, value_type>    iterator;
    typedef ft::tree_iterator<node_pointer, value_type>    const_iterator;
    typedef typename allocator_type_value::difference_type difference_type;
    typedef typename allocator_type_value::size_type       size_type;

    red_black_tree(const key_compare &comp, const allocator_type_value &alloc_value)
        : _root(NULL), _alloc_value(alloc_value), _comp(comp), _size(0) {
        _create_null();
        _root = _null;
        _left_most = _root;
        _right_most = _root;
    }

    red_black_tree(const red_black_tree &other) : _size(other.size()) {
        _create_null();
        _root = _null;
        _left_most = _root;
        _right_most = _root;
        _clone_tree(other);
    }

    ~red_black_tree() {
        clear();
        _destroy_node(_null);
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
                std::cout << n->key->second << "\033[37m\n";
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

    size_type max_size() const { return (_alloc_value.max_size()); }

    node_pointer search(node_pointer n, value_type key) {
        if (n == _null || _is_equal(*n->key, key))
            return (n);
        if (_is_less(key, *n->key))
            return (search(n->left, key));
        else
            return (search(n->right, key));
    }

    node_pointer iterative_search(node_pointer n, value_type key) {
        while (n != _null && _is_unequal(key, *n->key)) {
            if (_is_less(key, *n->key))
                n = n->left;
            else
                n = n->right;
        }
        return (n);
    }

    node_pointer successor(node_pointer n) {
        if (n->right != _null)
            return (min(n->right));
        node_pointer *p = n->parent;
        while (p != NULL && n == p->right) {
            n = p;
            p = p->parent;
        }
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

    ft::pair<iterator, bool> insert(const value_type &val) {
        if (_is_equal(*_root->key, val))
            return (ft::make_pair<iterator, bool>(iterator(_root), false));
        node_pointer needle = iterative_search(_root, val);
        if (needle != _root && needle != _null)
            return (ft::make_pair<iterator, bool>(iterator(needle), false));

        node_pointer input = _create_node(val);
        node_pointer n = _null;
        node_pointer r = _root;
        while (r != _null) {
            n = r;
            if (_is_less(*input->key, *r->key))
                r = r->left;
            else
                r = r->right;
        }
        input->parent = n;
        if (n == _null)
            _root = input;
        else if (_is_less(*input->key, *n->key))
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
        return (ft::make_pair<iterator, bool>(iterator(input), true));
    }

    iterator insert(iterator position, const value_type &val) {
        // if (_is_less(*position, val) && _is_less(successor(*position))) {
        //     transplant(*position, _create_node(val));
        // } else {
        (void)position;
        return (insert(val)).first;
        // }
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
            node_pointer         tmp_root = other._root;
            node_pointer         tmp_null = other._null;
            node_pointer         tmp_left_most = other._left_most;
            node_pointer         tmp_right_most = other._right_most;
            allocator_type_value tmp_alloc_value = other._alloc_value;
            allocator_type_node  tmp_alloc_node = other._alloc_node;

            other._root = _root;
            other._null = _null;
            other._left_most = _left_most;
            other._right_most = _right_most;
            other._alloc_value = _alloc_value;
            other._alloc_node = _alloc_node;
            _root = tmp_root;
            _null = tmp_null;
            _left_most = tmp_left_most;
            _right_most = tmp_right_most;
            _alloc_value = tmp_alloc_value;
            _alloc_node = tmp_alloc_node;
        }
    }

   private:
    node_pointer         _root;
    node_pointer         _null;
    node_pointer         _left_most;
    node_pointer         _right_most;
    allocator_type_value _alloc_value;
    allocator_type_node  _alloc_node;
    key_compare          _comp;
    size_type            _size;

    node_pointer _create_node(const value_type &val) {
        pointer cpy = _alloc_value.allocate(1);
        _alloc_value.construct(cpy, value_type(val));
        node_pointer n = _alloc_node.allocate(1);
        _alloc_node.construct(n, node(cpy, NULL, NULL, NULL));
        _size++;

        return (n);
    }

    void _create_null() {
        pointer null_val = _alloc_value.allocate(1);
        _alloc_value.construct(null_val, value_type(key_type(), mapped_type()));
        _null = _alloc_node.allocate(1);
        _alloc_node.construct(_null, node(null_val, NULL, NULL, NULL, BLACK, true));
    }

    void _destroy_node(node_pointer n) {
        _alloc_value.destroy(n->key);
        _alloc_value.deallocate(n->key, 1);
        _alloc_node.destroy(n);
        _alloc_node.deallocate(n, 1);
        _size--;
    }

    void _clone_tree(const red_black_tree &other) {
        for (iterator it = other.begin(); it != other.end(); ++it)
            insert(*it);
    }

    bool _is_equal(const value_type &val1, const value_type &val2) {
        return (!_comp(val1.first, val2.first) && !_comp(val2.first, val1.first));
    }

    bool _is_unequal(const value_type &val1, const value_type &val2) {
        return !(_is_equal(val1, val2));
    }

    bool _is_less(const value_type &val1, const value_type &val2) {
        return (_comp(val1.first, val2.first));
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