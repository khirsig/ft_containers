/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:32 by khirsig           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/21 15:02:42 by khirsig          ###   ########.fr       */
=======
/*   Updated: 2022/08/19 14:15:35 by khirsig          ###   ########.fr       */
>>>>>>> 4d731e9315379d0ba849cc2a30ae62538d33f7bc
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_HPP_
#define MAP_UTILS_HPP_

#ifdef TEST
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
// typedef NAMESPACE::pair<int, int> intpair;

void map_tests();

void debug_padding(std::string title, std::size_t width, char c);

template <class T>
void print_content(T &mp) {
    std::cout << "Content: ";
<<<<<<< HEAD
    for (typename T::iterator it = vec.begin(); it != vec.end(); ++it) {
=======
    for (typename T::iterator it = mp.begin(); it != mp.end(); ++it) {
>>>>>>> 4d731e9315379d0ba849cc2a30ae62538d33f7bc
        std::cout << "K: " << it->first << " V: " << it->second << " | ";
    }
    std::cout << "\n";
}

template <class T>
<<<<<<< HEAD
void print_content_reverse(T vec) {
    std::cout << "Content: ";
    for (typename T::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it) {
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
void print_size(T vec) {
    std::cout << "Size: " << vec.size() << "\n";
=======
void print_size(T &mp) {
    std::cout << "Size: " << mp.size() << "\n";
>>>>>>> 4d731e9315379d0ba849cc2a30ae62538d33f7bc
}

template <class T>
void print_all(T &mp, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content(mp);
    print_size(mp);
    debug_padding("", 30, '_');
}

template <class T>
void print_all_reverse(T vec, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content_reverse(vec);
    print_size(vec);
    debug_padding("", 30, '_');
}

#endif