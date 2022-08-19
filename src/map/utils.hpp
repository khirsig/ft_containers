/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 11:51:57 by khirsig          ###   ########.fr       */
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

typedef NAMESPACE::map<int, int> intmap;
typedef NAMESPACE::pair<int, int> intpair;

void 	map_tests();

void    debug_padding(std::string title, std::size_t width, char c);

template <class T>
void    print_content(T vec) {
    std::cout << "Content: ";
    for (typename T::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << "Key[" << it->first << "] Value[" << it->second << "] ";
    }
    std::cout << "\n";
}

template <class T>
void    print_size(T vec) {
    std::cout << "Size: " << vec.size() << "\n";
}

template <class T>
void print_all(T vec, std::string name) {
    debug_padding(name, 30, '_');
    std::cout << "\n";
    print_content(vec);
    print_size(vec);
    debug_padding("", 30, '_');
}

#endif