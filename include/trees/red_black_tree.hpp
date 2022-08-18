/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 12:26:29 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef red_black_TREE_HPP
#define red_black_TREE_HPP

#include <algorithm>
#include <functional>
#include <iostream>

#include "../iterators/tree_iterator.hpp"
#include "../iterators/tree_iterator_const.hpp"
#include "../utils/pair.hpp"
#include "./node.hpp"

namespace ft {

template <class Pair, class Key, class T, class Compare, class Alloc>
class red_black_tree {
   public:
    typedef Key                                                         key_type;
    typedef T                                                           mapped_type;
    typedef Pair                                                        value_type;
    typedef Compare                                                     key_compare;
    typedef Alloc                                                       allocator_type_value;
    typedef typename allocator_type_value::reference                    reference;
    typedef typename allocator_type_value::const_reference              const_reference;
    typedef typename allocator_type_value::pointer                      pointer;
    typedef typename allocator_type_value::const_pointer                const_pointer;
    typedef ft::node<value_type>                                        node;
    typedef typename allocator_type_value::template rebind<node>::other allocator_type_node;
    typedef typename ft::node<value_type>::node_pointer                 node_pointer;
    typedef typename ft::node<value_type>::const_node_pointer           const_node_pointer;
    typedef typename allocator_type_node::reference                     node_reference;
    typedef ft::tree_iterator<node_pointer, value_type>                 iterator;
    typedef ft::const_tree_iterator<const_node_pointer, value_type>     const_iterator;
    typedef ft::reverse_iterator<iterator>                              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
    typedef typename allocator_type_value::difference_type              difference_type;
    typedef typename allocator_type_value::size_type                    size_type;

    red_black_tree(const key_compare &comp, const allocator_type_value &alloc_value)
        : _root(NULL), _alloc_value(alloc_value), _alloc_node(alloc_value), _comp(comp), _size(0) {
        _create_null();
        _create_ends();
        _root = _past_end;
        _left_most = _root;
        _right_most = _root;
        _right_most->right = _past_end;
        _left_most->left = _past_begin;
    }

    red_black_tree(const red_black_tree &other)
        : _alloc_value(other._alloc_value), _alloc_node(other._alloc_node) {
        _create_null();
        _root = _clone(other._root, _null);
        if (_root != _null) {
            _left_most = tree_min(_root);
            _right_most = tree_max(_root);
        } else {
            _root = _past_end;
            _left_most = _past_end;
            _right_most = _past_end;
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
                _root = _past_end;
                _left_most = _past_end;
                _right_most = _past_end;
            }
            _right_most->right = _past_end;
            _left_most->left = _past_begin;
            _size = other._size;
        }
        return (*this);
    }

    iterator begin() { return _left_most; }

    const_iterator begin() const { return _left_most; }

    iterator end() { return _past_end; }

    const_iterator end() const { return _past_end; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool empty() const { return _size == 0 ? true : false; }

    size_type size() const { return (_size); }

    size_type max_size() const {
        size_type alloc_max = this->_alloc_node.max_size();
        size_type numeric_max = std::numeric_limits<difference_type>::max() / 2;
        return ((alloc_max < numeric_max) ? alloc_max : numeric_max);
    }

    mapped_type &operator[](const key_type &k) {
        return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
    }

    mapped_type &at(const key_type &k) {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _past_end || (needle == _root && _is_unequal(k, *_root->key)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    const mapped_type &at(const key_type &k) const {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _past_end || (needle == _root && _is_unequal(k, *_root->key)))
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

    template <class T1>
    node_pointer iterative_search(node_pointer n, const T1 &key) const {
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

    node_pointer successor(node_pointer n) {
        if (n->right != _past_end)
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
        if (!_root->is_leaf && _is_equal(*_root->key, val))
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
        input->color = red;
        _insert_fixup(input);
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
        return (ft::make_pair<iterator, bool>(iterator(input), true));
    }

    iterator insert(const_iterator position, const value_type &val) {
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

    template <class T1, class T2>
    void transplant(T1 target, T2 input) {
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
        } else if (input == _right_most) {
            if (input->left->is_leaf)
                _right_most = _right_most->parent;
            else
                _right_most = tree_max(_right_most->left);
        }
        if (y_original_color == black)
            _erase_fixup(x);
        _erase_node(input);
        if (_size != 0) {
            _left_most->left = _past_begin;
            _past_begin->parent = _left_most;
            _right_most->right = _past_end;
            _past_end->parent = _right_most;
        }
        if (_size == 0) {
            _root = _past_end;
            _left_most = _root;
            _right_most = _root;
            _right_most->right = _past_end;
            _left_most->left = _past_begin;
        }
    }

    void clear() {
        _clear(_root);
        _root = _past_end;
        _left_most = _root;
        _right_most = _root;
        _root->right = _past_end;
    };

    void swap(red_black_tree &other) {
        if (this != &other) {
            node_pointer         tmp_root = other._root;
            node_pointer         tmp_null = other._null;
            node_pointer         tmp_left_most = other._left_most;
            node_pointer         tmp_right_most = other._right_most;
            node_pointer         tmp_past_end = other._past_end;
            node_pointer         tmp_past_begin = other._past_begin;
            allocator_type_value tmp_alloc_value = other._alloc_value;
            allocator_type_node  tmp_alloc_node = other._alloc_node;
            size_type            tmp_size = other._size;

            other._root = _root;
            other._null = _null;
            other._left_most = _left_most;
            other._right_most = _right_most;
            other._past_end = _past_end;
            other._past_begin = _past_begin;
            other._alloc_value = _alloc_value;
            other._alloc_node = _alloc_node;
            other._size = _size;
            _root = tmp_root;
            _null = tmp_null;
            _left_most = tmp_left_most;
            _right_most = tmp_right_most;
            _past_end = tmp_past_end;
            _past_begin = tmp_past_begin;
            _alloc_value = tmp_alloc_value;
            _alloc_node = tmp_alloc_node;
            _size = tmp_size;
        }
    }

    iterator find(const key_type &k) {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _root != _past_end && _is_equal(*_root->key, k))
            return iterator(_root);
        else if (n == _root)
            return end();
        else
            return iterator(n);
    }

    const_iterator find(const key_type &k) const {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _root != _past_end && _is_equal(*_root->key, k))
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
            if (!_is_less(*n->key, k)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator lower_bound(const key_type &k) const {
        const_node_pointer result = end().base();
        node_pointer       n = _root;
        while (!n->is_leaf) {
            if (!_is_less(*n->key, k)) {
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
            if (_is_less(k, *n->key)) {
                result = n;
                n = n->left;
            } else
                n = n->right;
        }
        return iterator(result);
    }

    const_iterator upper_bound(const key_type &k) const {
        const_node_pointer result = end().base();
        node_pointer       n = _root;
        while (!n->is_leaf) {
            if (_is_less(k, *n->key)) {
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
        _alloc_value.construct(null_val, value_type());
        _null = _alloc_node.allocate(1);
        _alloc_node.construct(_null, node(null_val, NULL, NULL, NULL, black, true));
    }

    void _create_ends() {
        _past_end = _alloc_node.allocate(1);
        _alloc_node.construct(_past_end, node(NULL, _right_most, _null, _null, black, true, true));
        _past_begin = _alloc_node.allocate(1);
        _alloc_node.construct(_past_begin, node(NULL, _left_most, _null, _null, black, true, true));
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

    template <class T1, class T2>
    bool _is_equal(const T1 &val1, const T2 &val2) const {
        return (!_comp(val1, val2) && !_comp(val2, val1));
    }

    template <class T1, class T2>
    bool _is_unequal(const T1 &val1, const T2 &val2) const {
        return !(_is_equal(val1, val2));
    }

    template <class T1, class T2>
    bool _is_less(const T1 &val1, const T2 &val2) const {
        return (_comp(val1, val2));
    }

    void _erase_fixup(node_pointer x) {
        while (x != _root && x->color == black) {
            if (x == x->parent->left) {
                node_pointer w = x->parent->right;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == black && w->right->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->right->color == black) {
                        w->left->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    left_rotate(x->parent);
                    x = _root;
                }
            } else {
                node_pointer w = x->parent->left;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == black && w->left->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->left->color == black) {
                        w->right->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    right_rotate(x->parent);
                    x = _root;
                }
            }
        }
        x->color = black;
    }

    void _insert_fixup(node_pointer input) {
        while (input->parent->color == red) {
            if (input->parent == input->parent->parent->left) {
                node_pointer n = input->parent->parent->right;
                if (n->color == red) {
                    input->parent->color = black;
                    n->color = black;
                    input->parent->parent->color = red;
                    input = input->parent->parent;
                } else {
                    if (input == input->parent->right) {
                        input = input->parent;
                        left_rotate(input);
                    }
                    input->parent->color = black;
                    input->parent->parent->color = red;
                    right_rotate(input->parent->parent);
                }
            } else {
                node_pointer n = input->parent->parent->left;
                if (n->color == red) {
                    input->parent->color = black;
                    n->color = black;
                    input->parent->parent->color = red;
                    input = input->parent->parent;
                } else {
                    if (input == input->parent->left) {
                        input = input->parent;
                        right_rotate(input);
                    }
                    input->parent->color = black;
                    input->parent->parent->color = red;
                    left_rotate(input->parent->parent);
                }
            }
        }
        _root->color = black;
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
