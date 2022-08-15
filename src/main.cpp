/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/15 15:08:25 by khirsig          ###   ########.fr       */
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
    // std::cout << "Begin: " << (*map1.begin()).second << "  " << (*map2.begin()).second << "\n";
    // std::cout << "End: " << (*map1.end()).second << "  " << (*map2.end()).second << "\n\n";
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
    ft::map<int, int> map1, map2;

    for (int i = 1; i < 15; ++i) {
        map1.insert(ft::make_pair<const int, int>(i, i));
    }
    for (int i = 15; i < 30; ++i) {
        map2.insert(ft::make_pair<const int, int>(i, i));
    }

    // map1.print();
    // std::cout << "Before Swapping:\n\n";
    // compare_two_maps(map1, map2);
    // map1.swap(map2);
    // map2.erase(map2.begin());
    // map2.erase(map2.begin());
    // std::cout << "\nAfter Swapping:\n\n";
    // compare_two_maps(map1, map2);
    ft::map<int, std::string> m;

    // ft::map<std::string, std::string>::size_type size = m.erase("");
    m.insert(ft::make_pair(23, ""));
    m.insert(ft::make_pair(123, "kjhgfdsdffghsfghdfgh"));
    m.insert(ft::make_pair(1234, "gfdsadgg"));
    m.insert(ft::make_pair(12345678912345678, "49857459898674568464"));
    m.insert(ft::make_pair(5, "49857459898674568464"));
    m.insert(ft::make_pair(2, "49857459898674568464"));
    // m.insert(ft::make_pair("0", "2345456456456456"));
    // m.insert(ft::make_pair("", ""));
    // m.insert(ft::make_pair("", "9459845984598498"));
    // m.insert(ft::make_pair("000000000000000000000000", "1111111111111111111111111111"));

    // size = m.erase("1");
    for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); it = m.begin()) {
        std::cout << it->first << "\n";
        m.erase(it);
    }

    std::cout << "ENDE\n";
    return (0);
}
