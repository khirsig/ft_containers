/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/18 08:16:21 by khirsig          ###   ########.fr       */
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
#include "DebugBox.hpp"

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
    ft::DebugBox box(50);

    box.padding("Begin");
    typedef ft::map<int, std::string> strmap;

    strmap m;

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

    strmap::iterator it = m.end();
    // it++; it++; it++; it++;
    it--;
    for (; it != m.begin(); it--)
        std::cout << it->first << "\n";


     box.padding("Ending");

    return (0);
}
