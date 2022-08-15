/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/15 19:54:49 by khirsig          ###   ########.fr       */
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
    m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));

    for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); it = m.begin()) {
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
    // m.erase(25);
    m.erase(-23);

    // ft::map<int, std::string>::iterator iter = m.begin();
    // for (int i = 0; i < 6; ++i, iter = m.begin())
    //     m.erase(iter);
    std::cout << "erased all\n";
    m.insert(ft::make_pair(5, "49857459898674568464"));

    std::cout << "ENDE\n";
    return (0);
}
