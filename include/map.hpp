/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:11:24 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/12 10:57:16 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <algorithm>

#include "trees/red_black_tree.hpp"

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

    void print() { _tree.print(); }

    iterator begin() { return (_tree.begin()); }

    const_iterator begin() const { return (_tree.begin()); }

    iterator end() { return (_tree.end()); }

    const_iterator end() const { return (_tree.end()); }

    bool empty() const { return (_tree.empty()); }

    size_type size() const { return (_tree.size()); }

    size_type max_size() const { return (_tree.max_size()); }

    ft::pair<iterator, bool> insert(const value_type &val) { return (_tree.insert(val)); }

    iterator insert(iterator position, const value_type &val) {
        return (_tree.insert(position, val));
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        _tree.insert(first, last);
    }

    void erase(iterator position) { _tree.erase(position.base()); }

    void swap(map &x) { _tree.swap(x._tree); }

   private:
    ft::red_black_tree<key_type, mapped_type, key_compare, allocator_type> _tree;
};
}  // namespace ft

#endif