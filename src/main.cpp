/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/16 15:08:41 by khirsig          ###   ########.fr       */
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
    ft::map<int, std::string> m;

    m.insert(ft::make_pair(23, "23n"));
    m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
    m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
    m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
    m.insert(ft::make_pair(3, "sssdfs"));
    m.insert(ft::make_pair(75, "dfse"));
    m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
    m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
    m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
    m.insert(ft::make_pair(22, "98y4rtuohwidsjusdossefsse"));

    // int count = 0;
    std::cout << "Size:  " << m.size() << "\n\n";
    // for (ft::map<int, std::string>::reverse_iterator rit = m.rbegin(); rit != m.rend();
    //      ++rit, ++co3unt) {
    //     // std::cout << count + 1 << ":  " << rit->first
    //     //           << "   RightMost:  " << m._get_right_most()->first << "\n";
    // }

    // for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it) {
    //     std::cout << it->first << "\n";
    // }
    std::cout << "Begin: " << m.begin()->first << "\n";
    for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); it = m.begin()) {
        std::cout << m.size() << "  " << it->first << "\n";
        // std::cout << &(*m.begin()) << "  " << &(*m.end()) << "  " << &(*it) << "\n";
        m.erase(it);
    }

    m.insert(ft::make_pair(23, "23n"));
    m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
    m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
    m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
    m.insert(ft::make_pair(3, "sssdfs"));
    m.insert(ft::make_pair(75, "dfse"));
    m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
    m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
    m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
    m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));

    m.erase(64);
    m.erase(0);
    m.erase(75);
    m.erase(1);
    m.erase(2);
    m.erase(3);
    m.erase(23);
    m.erase(23);
    m.erase(30);
    m.erase(-22);
    m.erase(-23);
    m.erase(-23);
    m.erase(25);
    m.erase(-23);

    m.insert(ft::make_pair(23, "23n"));
    m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
    m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
    m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
    m.insert(ft::make_pair(3, "sssdfs"));
    m.insert(ft::make_pair(75, "dfse"));
    m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
    m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
    m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
    m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));

    for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); it = m.begin()) {
        std::cout << m.size() << "  " << it->first << "\n";
        // std::cout << &(*m.begin()) << "  " << &(*m.end()) << "  " << &(*it) << "\n";
        m.erase(it);
    }
    // ft::map<int, std::string>::iterator iter = m.begin();
    // for (int i = 0; i < 6; ++i, iter = m.begin())
    //     m.erase(iter);
    // std::cout << "erased all\n";
    // m.insert(ft::make_pair(5, "49857459898674568464"));

    std::cout << "ENDE\n";
    return (0);
}
