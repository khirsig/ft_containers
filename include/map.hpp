/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:11:24 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/15 15:48:05 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <algorithm>

#include "iterators/reverse_iterator.hpp"
#include "trees/red_black_tree.hpp"
#include "utils/lexicographical_compare.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<const Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
   public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef ft::pair<const key_type, mapped_type>       value_type;
    typedef Compare                                     key_compare;
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef ft::node<value_type>                        node;
    typedef node                                       *node_pointer;
    typedef node                                       &node_reference;
    typedef ft::tree_iterator<node_pointer, value_type> iterator;
    typedef ft::tree_iterator<node_pointer, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    typedef typename allocator_type::difference_type    difference_type;
    typedef typename allocator_type::size_type          size_type;

    explicit map(const key_compare    &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _tree(comp, alloc) {}

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _tree(comp, alloc) {
        _tree.insert(first, last);
    }

    map(const map &x) : _tree(x._tree) {}

    ~map() {}

    map &operator=(const map &x) {
        _tree = x._tree;
        return (*this);
    }

    void print() { _tree.print(); }

    iterator begin() { return _tree.begin(); }

    const_iterator begin() const { return _tree.begin(); }

    iterator end() { return _tree.end(); }

    const_iterator end() const { return _tree.end(); }

    reverse_iterator rbegin() { return _tree._right_most; }

    const_reverse_iterator rbegin() const { return _tree._right_most; }

    bool empty() const { return _tree.empty(); }

    size_type size() const { return _tree.size(); }

    size_type max_size() const { return _tree.max_size(); }

    mapped_type &operator[](const key_type &k) { return _tree[k]; }

    mapped_type &at(const key_type &k) { return _tree.at(k); }

    const mapped_type &at(const key_type &k) const { return _tree.at(k); }

    ft::pair<iterator, bool> insert(const value_type &val) { return (_tree.insert(val)); }

    iterator insert(iterator position, const value_type &val) {
        return (_tree.insert(position, val));
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        _tree.insert(first, last);
    }

    void erase(iterator position) { _tree.erase(position.base()); }

    size_type erase(const key_type &k) {
        size_type cnt = 0;
        iterator  it;
        while ((it = find(k)) != end()) {
            erase(it);
            ++cnt;
        }
        return cnt;
    }

    void erase(iterator first, iterator last) {
        for (; first != last; ++first) {
            std::cout << "111\n";
            erase(first);
        }
    }

    void clear() { _tree.clear(); }

    void swap(map &x) { _tree.swap(x._tree); }

    iterator find(const key_type &k) { return _tree.find(k); }

    const_iterator find(const key_type &k) const { return _tree.find(k); }

    key_compare key_comp() const { return key_compare(); }

    size_type count(const key_type &k) const { return find(k) != end() ? 1 : 0; }

    iterator lower_bound(const key_type &k) { return _tree.lower_bound(k); }

    const_iterator lower_bound(const key_type &k) const { return _tree.lower_bound(k); }

    iterator upper_bound(const key_type &k) { return _tree.upper_bound(k); }

    const_iterator upper_bound(const key_type &k) const { return _tree.upper_bound(k); }

    ft::pair<iterator, iterator> equal_range(const key_type &key) { return _tree.equal_range(key); }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
        return _tree.equal_range(key);
    }

    allocator_type get_allocator() const { return _tree.get_allocator(); }

    class value_compare : public std::binary_function<value_type, value_type, bool> {
        friend class map;

       public:
        typedef bool       result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type &x, const value_type &y) const {
            return comp(x.first, y.first);
        }

       protected:
        value_compare(Compare c) : comp(c) {}
        Compare comp;
    };

    value_compare value_comp() const { return value_compare(); }

   private:
    ft::red_black_tree<key_type, mapped_type, key_compare, allocator_type> _tree;
};

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs) {
    lhs.swap(rhs);
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator==(const map<Key, T, Compare, Alloc> &lhs,
                       const map<Key, T, Compare, Alloc> &rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                       const map<Key, T, Compare, Alloc> &rhs) {
    return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator<(const map<Key, T, Compare, Alloc> &lhs,
                      const map<Key, T, Compare, Alloc> &rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator>(const map<Key, T, Compare, Alloc> &lhs,
                      const map<Key, T, Compare, Alloc> &rhs) {
    return rhs < lhs;
}
template <class Key, class T, class Compare, class Alloc>
inline bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                       const map<Key, T, Compare, Alloc> &rhs) {
    return !(rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
inline bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                       const map<Key, T, Compare, Alloc> &rhs) {
    return !(lhs < rhs);
}

}  // namespace ft

#endif