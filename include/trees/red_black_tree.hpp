/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:35:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 15:39:18 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef red_black_TREE_HPP
#define red_black_TREE_HPP

#include <algorithm>
#include <functional>
#include <limits>

#include "../iterators/tree_iterator.hpp"
#include "../iterators/tree_iterator_const.hpp"
#include "../utils/pair.hpp"
#include "./node.hpp"

namespace ft {

template <class Pair, class Key, class T, class Compare, class Alloc>
class red_black_tree {
   public:
    typedef Key                                                     key_type;
    typedef T                                                       mapped_type;
    typedef Pair                                                    value_type;
    typedef Compare                                                 key_compare;
    typedef Alloc                                                   allocator_type;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef ft::node<value_type>                                    node;
    typedef typename allocator_type::template rebind<node>::other   allocator_type_node;
    typedef typename ft::node<value_type>::node_pointer             node_pointer;
    typedef typename ft::node<value_type>::const_node_pointer       const_node_pointer;
    typedef typename allocator_type_node::reference                 node_reference;
    typedef ft::tree_iterator<node_pointer, value_type>             iterator;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
    typedef typename allocator_type::difference_type                difference_type;
    typedef typename allocator_type::size_type                      size_type;

    red_black_tree(const key_compare &comp, const allocator_type &alloc_value)
        : _root(NULL), _alloc_value(alloc_value), _alloc_node(alloc_value), _comp(comp), _size(0) {
        _create_null();
        _create_head();
        _root = _null;
        _left_most = _head;
        _root->parent = _head;
        _head->left = _root;
    }

    red_black_tree(const red_black_tree &other)
        : _root(NULL),
          _alloc_value(other._alloc_value),
          _alloc_node(other._alloc_node),
          _comp(other._comp),
          _size(0) {
        _create_null();
        _create_head();
        _root = _clone(other._root, _head);
        if (_root != _null) {
            _left_most = tree_min(_root);
        } else {
            _left_most = _head;
        }
        _head->left = _root;
    }

    ~red_black_tree() {
        clear();
        _erase_node(_null);
        _erase_node(_head);
    }

    red_black_tree &operator=(const red_black_tree &other) {
        if (this != &other) {
            if (size() > 0 && _root != _null)
                clear();
            _root = _clone(other._root, _head);
            if (_root != _null) {
                _left_most = tree_min(_root);
            } else {
                _left_most = _head;
            }
            _head->left = _root;
            _size = other._size;
        }
        return (*this);
    }

    iterator begin() { return _left_most; }

    const_iterator begin() const { return _left_most; }

    iterator end() { return _head; }

    const_iterator end() const { return _head; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool empty() const { return _size == 0 ? true : false; }

    size_type size() const { return (_size); }

    size_type max_size() const {
        size_type alloc_max = this->_alloc_node.max_size();
        size_type numeric_max = std::numeric_limits<difference_type>::max();
        return alloc_max < numeric_max ? alloc_max : numeric_max;
    }

    mapped_type &operator[](const key_type &k) {
        return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
    }

    mapped_type &at(const key_type &k) {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _null || (needle == _root && _is_unequal(k, *_root->key)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    const mapped_type &at(const key_type &k) const {
        node_pointer needle = iterative_search(_root, k);
        if (_root == _null || (needle == _root && _is_unequal(k, *_root->key)))
            throw(std::out_of_range("map"));
        return (*needle->key).second;
    }

    node_pointer search(node_pointer n, const value_type &key) const {
        if (n == _null || _is_equal(*n->key, key))
            return (n);
        if (_is_less(key, *n->key))
            return (search(n->left, key));
        else
            return (search(n->right, key));
    }

    template <class T1>
    node_pointer iterative_search(node_pointer n, const T1 &key) const {
        while (n != _null && _is_unequal(key, *n->key)) {
            if (_is_less(key, *n->key))
                n = n->left;
            else
                n = n->right;
        }
        if (n == _null)
            return (_root);
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
        if (_root != _null && _is_equal(*_root->key, val))
            return (ft::make_pair<iterator, bool>(iterator(_root), false));
        node_pointer needle = iterative_search(_root, val);
        if (needle != _root && needle != _null)
            return (ft::make_pair<iterator, bool>(iterator(needle), false));

        node_pointer z = _create_node(val);
        node_pointer y = _head;
        node_pointer x = _root;
        while (x != _null) {
            y = x;
            if (_is_less(*z->key, *x->key))
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == _head) {
            _root = z;
            _root->parent = _head;
            _head->left = _root;
            _left_most = z;
        } else if (_is_less(*z->key, *y->key)) {
            y->left = z;
            if (_left_most == y)
                _left_most = z;
        } else
            y->right = z;
        z->left = _null;
        z->right = _null;
        z->color = red;
        _insert_fixup(z);
        // _left_most = tree_min(_root);
        // _root->parent = _head;
        return (ft::make_pair<iterator, bool>(iterator(z), true));
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
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    template <class T1, class T2>
    void transplant(T1 u, T2 v) {
        if (u->parent == _null)
            _root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void erase(node_pointer z) {
        node_pointer y = z;
        node_pointer x;
        color        y_original_color = y->color;
        if (z->left == _null) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == _null) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = tree_min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (z == _left_most) {
            if (z->right == _null)
                _left_most = _left_most->parent;
            else
                _left_most = tree_min(_left_most->right);
        }
        if (y_original_color == black)
            _erase_fixup(x);
        _erase_node(z);
        // _left_most = tree_min(_root);
    }

    void clear() {
        _clear(_root);
        _root = _null;
        _root->parent = _head;
        _left_most = _head;
    };

    void swap(red_black_tree &other) {
        if (this != &other) {
            node_pointer        tmp_root = other._root;
            node_pointer        tmp_null = other._null;
            node_pointer        tmp_head = other._head;
            allocator_type      tmp_alloc_value = other._alloc_value;
            allocator_type_node tmp_alloc_node = other._alloc_node;
            size_type           tmp_size = other._size;

            other._root = _root;
            other._null = _null;
            other._head = _head;
            other._alloc_value = _alloc_value;
            other._alloc_node = _alloc_node;
            other._size = _size;
            _root = tmp_root;
            _null = tmp_null;
            _head = tmp_head;
            _alloc_value = tmp_alloc_value;
            _alloc_node = tmp_alloc_node;
            _size = tmp_size;
        }
    }

    iterator find(const key_type &k) {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _root != _null && _is_equal(*_root->key, k))
            return iterator(_root);
        else if (n == _root) {
            return end();
        } else
            return iterator(n);
    }

    const_iterator find(const key_type &k) const {
        node_pointer n = iterative_search(_root, k);
        if (n == _root && _root != _null && _is_equal(*_root->key, k))
            return const_iterator(_root);
        else if (n == _root)
            return const_iterator(end());
        else
            return const_iterator(n);
    }

    iterator lower_bound(const key_type &k) {
        node_pointer result = end().base();
        node_pointer n = _root;
        while (n != _null) {
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
        while (n != _null) {
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
        while (n != _null) {
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
        while (n != _null) {
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

    allocator_type get_allocator() const { return _alloc_value; }

   private:
    node_pointer        _root;
    node_pointer        _null;
    node_pointer        _left_most;
    node_pointer        _head;
    allocator_type      _alloc_value;
    allocator_type_node _alloc_node;
    key_compare         _comp;
    size_type           _size;

    node_pointer _create_node(const value_type &val) {
        pointer cpy = _alloc_value.allocate(1);
        _alloc_value.construct(cpy, value_type(val));
        node_pointer n = _alloc_node.allocate(1);
        _alloc_node.construct(n, node(cpy, NULL, NULL, NULL));
        _size++;

        return (n);
    }

    node_pointer _copy_node(const value_type &val, color &col) {
        pointer cpy = _alloc_value.allocate(1);
        _alloc_value.construct(cpy, value_type(val));
        node_pointer n = _alloc_node.allocate(1);
        _alloc_node.construct(n, node(cpy, NULL, NULL, NULL, col));
        _size++;

        return (n);
    }

    void _create_null() {
        pointer null_val = _alloc_value.allocate(1);
        _alloc_value.construct(null_val, value_type());
        _null = _alloc_node.allocate(1);
        _alloc_node.construct(_null, node(null_val, NULL, NULL, NULL, black, true));
    }

    void _create_head() {
        _head = _alloc_node.allocate(1);
        _alloc_node.construct(_head, node(NULL, _root, _null, _null, black, false));
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
        if (n != _null) {
            _clear(n->left);
            _clear(n->right);
            _erase_node(n);
        }
    }

    node_pointer _clone(const node_pointer n, const node_pointer parent) {
        node_pointer cpy = _null;
        if (!n->is_leaf) {
            cpy = _copy_node(*(n->key), n->color);
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
