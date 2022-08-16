/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/16 12:35:26 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <algorithm>
#include <functional>
#include <iostream>

#include "../iterators/tree_iterator.hpp"
#include "../utils/pair.hpp"
#include "./node.hpp"

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
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    typedef typename allocator_type_node::difference_type  difference_type;
    typedef typename allocator_type_node::size_type        size_type;

    red_black_tree(const key_compare &comp, const allocator_type_value &alloc_value)
        : _root(NULL), _alloc_value(alloc_value), _comp(comp), _size(0) {
        _create_null();
        _create_ends();
        _root = _null;
        _left_most = _root;
        _right_most = _root;
        _right_most->right = _past_end;
        _left_most->left = _past_begin;
    }

    red_black_tree(const red_black_tree &other) {
        _create_null();
        _root = _clone(other._root, _null);
        if (_root != _null) {
            _left_most = tree_min(_root);
            _right_most = tree_max(_root);
        } else {
            _left_most = _null;
            _right_most = _null;
        }
        _create_ends();
        _right_most->right = _past_end;
        _left_most->left = _past_begin;
        _size = other._size;
    }

    ~red_black_tree() {
        clear();
        _erase_node(_null);
        _erase_node(_past_end);
        _erase_node(_past_begin);
    }

    red_black_tree &operator=(const red_black_tree &other) {
        if (this != &other) {
            if (size() > 0 && _root != _null)
                clear();
            _root = _clone(other._root, _null);
            if (_root != _null) {
                _left_most = tree_min(_root);
                _right_most = tree_max(_root);
            } else {
                _left_most = _null;
                _right_most = _null;
            }
            _right_most->right = _past_end;
             _left_most->left = _past_begin;
            _size = other._size;
        }
        return (*this);
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
            if (n != _null && n != _past_end)
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

    iterator begin() { return _left_most != _null ? _left_most : _root; }

    const_iterator begin() const { return _left_most != _null ? _left_most : _root; }

    iterator end() { return _null != _root ? _past_end : _root; }

    const_iterator end() const { return _null != _root ? _past_end : _root; }

    reverse_iterator rbegin() { return _right_most != _null ? reverse_iterator(_right_most) : reverse_iterator(_root); }

    const_reverse_iterator rbegin() const { return _right_most != _null ? const_reverse_iterator(_right_most) : const_reverse_iterator(_root); }

    reverse_iterator rend() { return _null != _root ? reverse_iterator(_past_begin) : reverse_iterator(_root); }

    const_reverse_iterator rend() const { return _null != _root ? const_reverse_iterator(_past_begin) : const_reverse_iterator(_root); }

    bool empty() const { return _size == 0 ? true : false; }

    size_type size() const { return (_size); }

    size_type max_size() const { return _alloc_node.max_size(); }

    mapped_type &operator[](const key_type &k) {
        return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
    }

    mapped_type &at(const key_type &k) {
        node_pointer needle = iterative_search(_root, k);
        if (_null == _root || (needle == _root && _is_unequal(k, (*_root->key).first)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    const mapped_type &at(const key_type &k) const {
        node_pointer needle = iterative_search(_root, k);
        if (_null == _root || (needle == _root && _is_unequal(k, (*_root->key).first)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    node_pointer search(node_pointer n, const value_type &key) const {
        if (n->is_leaf || _is_equal(*n->key, key))
            return (n);
        if (_is_less(key, *n->key))
            return (search(n->left, key));
        else
            return (search(n->right, key));
    }

    node_pointer iterative_search(node_pointer n, const value_type &key) const {
        while (!n->is_leaf && _is_unequal(key, *n->key)) {
            if (_is_less(key, *n->key))
                n = n->left;
            else
                n = n->right;
        }
        if (n->is_leaf)
            return (_root);
        return (n);
    }

    node_pointer iterative_search(node_pointer n, const key_type &key) const {
        while (!n->is_leaf && _is_unequal(key, (*n->key).first)) {
            if (_is_less(key, (*n->key).first))
                n = n->left;
            else
                n = n->right;
        }
        if (n->is_leaf)
            return (_root);
        return (n);
    }

    node_pointer successor(node_pointer n) {
        if (/*n->right != _null &&*/ n->right != _past_end)
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
        if (!y->left->is_leaf)
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
        if (!y->right->is_leaf)
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
        if (needle != _root && !needle->is_leaf)
            return (ft::make_pair<iterator, bool>(iterator(needle), false));

        node_pointer input = _create_node(val);
        node_pointer n = _null;
        node_pointer r = _root;
        while (!r->is_leaf) {
            n = r;
            if (_is_less(*input->key, *r->key))
                r = r->left;
            else
                r = r->right;
        }
        input->parent = n;
        if (n->is_leaf)
            _root = input;
        else if (_is_less(*input->key, *n->key))
            n->left = input;
        else
            n->right = input;
        input->left = _null;
        input->right = _null;
        input->color = RED;
        if (_left_most->left == input || _size == 1) {
            _left_most = input;
            _left_most->left = _past_begin;
            _past_begin->parent = _left_most;
        }
        if (_right_most->right == input || _size == 1) {
            _right_most = input;
            _right_most->right = _past_end;
            _past_end->parent = _right_most;
        }
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

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (; first != last; ++first)
            insert(*first);
    }

    void transplant(node_pointer target, node_pointer input) {
        if (target->parent->is_leaf)
            _root = input;
        else if (target == target->parent->left)
            target->parent->left = input;
        else
            target->parent->right = input;
        input->parent = target->parent;
    }

    void erase(node_pointer input) {
        node_pointer y = input;
        node_pointer x;
        color        y_original_color = y->color;

        if (input->left->is_leaf) {
            x = input->right;
            transplant(input, input->right);
        } else if (input->right->is_leaf) {
            x = input->left;
            transplant(input, input->left);
        } else {
            y = tree_min(input->right);
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
        if (input == _left_most) {
            if (input->right->is_leaf)
                _left_most = _left_most->parent;
            else
                _left_most = tree_min(_left_most->right);
            _left_most->left = _past_begin;
            _past_begin->parent = _left_most;
        } else if (input == _right_most) {
            if (input->left->is_leaf)
                _right_most = _right_most->parent;
            else
                _right_most = tree_max(_right_most->left);
            _right_most->right = _past_end;
            _past_end->parent = _right_most;
        }
        if (y_original_color == BLACK)
            _erase_fixup(x);
        _erase_node(input);
        if (_size == 0) {
            _root = _null;
            _left_most = _root;
            _right_most = _root;
            _right_most->right = _past_end;
            _left_most->left = _past_begin;
        }
    }

    void clear() {
        _clear(_root);
        _left_most = _null;
        _right_most = _null;
        _root = _null;
        _root->right = _past_end;
        _past_end->parent = _root;
    };

    void swap(red_black_tree &other) {
        if (this != &other) {
            node_pointer         tmp_root = other._root;
            node_pointer         tmp_null = other._null;
            node_pointer         tmp_left_most = other._left_most;
            node_pointer         tmp_right_most = other._right_most;
            node_pointer         tmp_past_end = other._past_end;
            allocator_type_value tmp_alloc_value = other._alloc_value;
            allocator_type_node  tmp_alloc_node = other._alloc_node;
            size_type            tmp_size = other._size;

            other._root = _root;
            other._null = _null;
            other._left_most = _left_most;
            other._right_most = _right_most;
            other._past_end = _past_end;
            other._alloc_value = _alloc_value;
            other._alloc_node = _alloc_node;
            other._size = _size;
            _root = tmp_root;
            _null = tmp_null;
            _left_most = tmp_left_most;
            _right_most = tmp_right_most;
            _past_end = tmp_past_end;
            _alloc_value = tmp_alloc_value;
            _alloc_node = tmp_alloc_node;
            _size = tmp_size;
        }
    }

    iterator find(const key_type &k) {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _is_equal((*_root->key).first, k))
            return iterator(_root);
        else if (n == _root)
            return end();
        else
            return iterator(n);
    }

    const_iterator find(const key_type &k) const {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _is_equal((*_root->key).first, k))
            return const_iterator(_root);
        else if (n == _root)
            return const_iterator(end());
        else
            return const_iterator(n);
    }

    iterator lower_bound(const key_type &k) {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (!n->is_leaf) {
            if (!_is_less((*n->key).first, k)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator lower_bound(const key_type &k) const {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (!n->is_leaf) {
            if (!_is_less((*n->key).first, k)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return const_iterator(result);
    }

    iterator upper_bound(const key_type &k) {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (!n->is_leaf) {
            if (_is_less(k, (*n->key).first)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator upper_bound(const key_type &k) const {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (!n->is_leaf) {
            if (_is_less(k, (*n->key).first)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return const_iterator(result);
    }

    ft::pair<iterator, iterator> equal_range(const key_type &key) {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    allocator_type_value get_allocator() const { return _alloc_value; }

   private:
    node_pointer         _root;
    node_pointer         _null;
    node_pointer         _left_most;
    node_pointer         _right_most;
    node_pointer         _past_end;
    node_pointer         _past_begin;
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

    void _create_ends() {
        _past_end = _alloc_node.allocate(1);
        _alloc_node.construct(_past_end,
                              node(NULL, _right_most, _null, _null, BLACK, true, true));
        _past_begin = _alloc_node.allocate(1);
        _alloc_node.construct(_past_begin,
                              node(NULL, _left_most, _null, _null, BLACK, true, true));
    }

    void _erase_node(node_pointer n) {
        if (n) {
            if (n->key) {
                _alloc_value.destroy(n->key);
                _alloc_value.deallocate(n->key, 1);
            }
            _alloc_node.destroy(n);
            _alloc_node.deallocate(n, 1);
            _size--;
        }
    }

    void _clear(node_pointer n) {
        if (!n->is_leaf) {
            _clear(n->left);
            _clear(n->right);
            _erase_node(n);
        }
    }

    node_pointer _clone(const node_pointer n, const node_pointer parent) {
        node_pointer cpy = _null;
        if (!n->is_leaf && !n->is_end) {
            cpy = _create_node(*(n->key));
            cpy->parent = parent;
            cpy->left = _clone(n->left, cpy);
            cpy->right = _clone(n->right, cpy);
        }
        return (cpy);
    }

    bool _is_equal(const value_type &val1, const value_type &val2) const {
        return (!_comp(val1.first, val2.first) && !_comp(val2.first, val1.first));
    }

    bool _is_equal(const key_type &val1, const key_type &val2) const {
        return (!_comp(val1, val2) && !_comp(val2, val1));
    }

    bool _is_unequal(const value_type &val1, const value_type &val2) const {
        return !(_is_equal(val1, val2));
    }

    bool _is_unequal(const key_type &val1, const key_type &val2) const {
        return !(_is_equal(val1, val2));
    }

    bool _is_less(const value_type &val1, const value_type &val2) const {
        return (_comp(val1.first, val2.first));
    }

    bool _is_less(const key_type &val1, const key_type &val2) const { return (_comp(val1, val2)); }

    void _erase_fixup(node_pointer x) {
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
