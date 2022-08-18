/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 15:03:58 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#include "../include/iterators/tree_iterator.hpp"
#include "../include/map.hpp"
#include "../include/utils/pair.hpp"

template <class T, class U>
void compare_two_maps(ft::map<T, U> &map1, ft::map<T, U> &map2) {
    typename ft::map<T, U>::iterator it1 = map1.begin(), it2 = map2.begin();
    std::cout << "Begin: " << (*map1.begin()).second << "  " << (*map2.begin()).second << "\n";
    std::cout << "End: " << (*map1.end()).second << "  " << (*map2.end()).second << "\n\n";
    while (it1 != map1.end() && it2 != map2.end()) {
        if (it1 != map1.end()) {
            std::cout << it1->second;
            ++it1;
        }
        std::cout << " ";
        if (it2 != map2.end()) {
            std::cout << it2->second;
            ++it2;
        }
        std::cout << "\n";
    }
}

int main() {
    typedef ft::map<int, int> intmap;

    intmap data;

    srand(time(NULL));
    for (int i = 0; i < 30; ++i)
        data.insert(ft::make_pair(i, i));

    intmap m(data);
    std::cout << m.size() << data.size() << "\n";
    for (int i = 0; i < 40; ++i) {
        m.erase(m.begin());
    }
    // m.insert(ft::make_pair(4, 4));
    // m.erase(m.begin());
    return (0);
}
