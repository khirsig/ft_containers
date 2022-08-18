/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:45:24 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 09:49:21 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP_
#define SET_HPP_

#include <algorithm>

#include "iterators/reverse_iterator.hpp"
#include "trees/red_black_tree.hpp"
#include "utils/lexicographical_compare.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set {
   public:
    typedef Key                                      key_type;
    typedef Key                                      value_type;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef Compare                                  key_compare;
    // typedef Compare                                                 value_compare;
    typedef value_type&                                             reference;
    typedef const value_type&                                       const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef node<value_type>                                        node_type;
    typedef typename ft::node<value_type>::node_pointer             node_pointer;
    typedef typename ft::node<value_type>::const_node_pointer       const_node_pointer;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> iterator;
    typedef ft::const_tree_iterator<const_node_pointer, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

    explicit set(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : _tree(comp, alloc) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : _tree(comp, alloc) {
        _tree.insert(first, last);
    }

    set(const set& x) : _tree(x._tree) {}

    ~set() {}

    set& operator=(const set& x) {
        _tree = x._tree;
        return *this;
    }

    allocator_type get_allocator() const { return _tree.get_allocator(); }

    iterator begin() { return _tree.begin(); }

    const_iterator begin() const { return _tree.begin(); }

    iterator end() { return _tree.end(); }

    const_iterator end() const { return _tree.end(); }

    reverse_iterator rbegin() { return _tree.rbegin(); }

    const_reverse_iterator rbegin() const { return _tree.rbegin(); }

    reverse_iterator rend() { return _tree.rend(); }

    const_reverse_iterator rend() const { return _tree.rend(); }

    bool empty() const { return _tree.empty(); }

    size_type size() const { return _tree.size(); }

    size_type max_size() const { return _tree.max_size(); }

    ft::pair<iterator, bool> insert(const value_type& val) { return (_tree.insert(val)); }

    iterator insert(iterator position, const value_type& val) {
        return (_tree.insert(position, val));
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        _tree.insert(first, last);
    }

    void erase(iterator position) { _tree.erase(position.base()); }

    size_type erase(const value_type& val) {
        size_type cnt = 0;
        iterator  it;
        while ((it = find(val)) != end()) {
            erase(it);
            ++cnt;
        }
        return cnt;
    }

    void erase(iterator first, iterator last) {
        for (iterator tmp = first; tmp != last; tmp = first) {
            first++;
            erase(tmp);
        }
    }

    void swap(set& x) { _tree.swap(x._tree); }

    void clear() { _tree.clear(); }

    key_compare key_comp() const { return key_compare(); }

    class value_compare {
        friend class set;

       public:
        typedef bool       result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }

       protected:
        value_compare(Compare c) : comp(c) {}
        Compare comp;
    };

    value_compare value_comp() const { return value_compare(key_compare()); }

    iterator find(const value_type& val) const { return _tree.find(val); }

    size_type count(const value_type& k) const { return find(k) != end() ? 1 : 0; }

    iterator lower_bound(const value_type& k) const { return _tree.lower_bound(k); }

    iterator upper_bound(const value_type& k) const { return _tree.upper_bound(k); }

    ft::pair<iterator, iterator> equal_range(const value_type& val) const {
        return _tree.equal_range(val);
    }

   private:
    ft::red_black_tree<value_type, key_type, value_type, key_compare, allocator_type> _tree;
};

template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs) {
    lhs.swap(rhs);
}

template <class Key, class Compare, class Alloc>
inline bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class Compare, class Alloc>
inline bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
inline bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class Compare, class Alloc>
inline bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return rhs < lhs;
}
template <class Key, class Compare, class Alloc>
inline bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return !(rhs < lhs);
}
template <class Key, class Compare, class Alloc>
inline bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
    return !(lhs < rhs);
}

}  // namespace ft

#endif