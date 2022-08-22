/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 09:59:12 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_UTILS_HPP_
#define SET_UTILS_HPP_

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

#include <iostream>
#include <set>

#include "../../include/set.hpp"

typedef NAMESPACE::set<int>         intset;
typedef NAMESPACE::set<std::string> strset;

void tests();

void debug_padding(std::string title, std::size_t width, char c);

template <class T>
void print_content(T s) {
    std::cout << "Content: ";
    for (typename T::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " | ";
    }
    std::cout << "\n";
}

template <class T>
void print_content_reverse(T s) {
    std::cout << "Content: ";
    for (typename T::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it << " | ";
    }
    std::cout << "\n";
}

template <class T>
void print_one(T it) {
    std::cout << "\n"
              << "Element: " << *it << "\n";
}

template <class T>
void print_size(T s) {
    std::cout << "Size: " << s.size() << "\n";
}

template <class T>
void print_all(T s, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content(s);
    print_size(s);
    debug_padding("", 30, '_');
}

template <class T>
void print_all_reverse(T s, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content_reverse(s);
    print_size(s);
    debug_padding("", 30, '_');
}

template <class T>
void comparison_operators(T s1, T s2, std::string name1, std::string name2) {
    debug_padding(name1 + " & " + name2, 30, '_');
    std::cout << "\n";
    if (s1 == s2)
        std::cout << name1 << " is equal to " << name2 << "\n";
    if (s1 != s2)
        std::cout << name1 << " is unequal to " << name2 << "\n";
    if (s1 > s2)
        std::cout << name1 << " is bigger as " << name2 << "\n";
    if (s1 < s2)
        std::cout << name1 << " is smaller as " << name2;
    debug_padding("", 30, '_');
}

#endif