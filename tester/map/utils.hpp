/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 09:59:20 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_HPP_
#define MAP_UTILS_HPP_

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>

#include "../../include/map.hpp"

typedef NAMESPACE::map<int, int>                 intmap;
typedef NAMESPACE::map<std::string, std::string> strmap;

void tests();

void debug_padding(std::string title, std::size_t width, char c);

template <class T>
void print_content(T mp) {
    std::cout << "Content: ";
    for (typename T::iterator it = mp.begin(); it != mp.end(); ++it) {
        std::cout << "K: " << it->first << " V: " << it->second << " | ";
    }
    std::cout << "\n";
}

template <class T>
void print_content_reverse(T mp) {
    std::cout << "Content: ";
    for (typename T::reverse_iterator it = mp.rbegin(); it != mp.rend(); ++it) {
        std::cout << "K: " << it->first << " V: " << it->second << " | ";
    }
    std::cout << "\n";
}

template <class T>
void print_one(T it) {
    std::cout << "\n"
              << "Element: "
              << "K: " << it->first << " V: " << it->second << "\n";
}

template <class T>
void print_size(T mp) {
    std::cout << "Size: " << mp.size() << "\n";
}

template <class T>
void print_all(T mp, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content(mp);
    print_size(mp);
    debug_padding("", 30, '_');
}

template <class T>
void print_all_reverse(T mp, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content_reverse(mp);
    print_size(mp);
    debug_padding("", 30, '_');
}

template <class T>
void comparison_operators(T mp1, T mp2, std::string name1, std::string name2) {
    debug_padding(name1 + " & " + name2, 30, '_');
    std::cout << "\n";
    if (mp1 == mp2)
        std::cout << name1 << " is equal to " << name2 << "\n";
    if (mp1 != mp2)
        std::cout << name1 << " is unequal to " << name2 << "\n";
    if (mp1 > mp2)
        std::cout << name1 << " is bigger as " << name2 << "\n";
    if (mp1 < mp2)
        std::cout << name1 << " is smaller as " << name2;
    debug_padding("", 30, '_');
}

#endif