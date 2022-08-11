/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/11 11:31:30 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../include/iterators/tree_iterator.hpp"
#include "../include/map.hpp"
#include "../include/utils/pair.hpp"

template <class T, class U>
void compare_two_maps(ft::map<T, U> &map1, ft::map<T, U> &map2) {
    typename ft::map<T, U>::iterator it1 = map1.begin(), it2 = map2.begin();
    while (it1 != map1.end() && it2 != map2.end()) {
        if (it1 != map1.end()) {
            std::cout << (*it1).second << " ";
            ++it1;
        }
        if (it2 != map2.end()) {
            std::cout << (*it2).second << "\n";
            ++it2;
        }
    }
    std::cout << (*it1).second << " " << (*it2).second << "\n";
}

int main() {
    // typedef ft::red_black_tree<ft::pair<const int, int> > rbtree;
    // rbtree                                                tree1, tree2;

    // for (int i = 1; i < 15; ++i) {
    //     tree1.insert(ft::make_pair<const int, int>(i, i));
    // }
    // for (int i = 15; i < 30; ++i) {
    //     ft::pair<const int, int>         tmp = ft::make_pair(i, i);
    //     ft::pair<rbtree::iterator, bool> pr = tree2.insert(tmp);
    //     std::cout << pr.first->key.first << "\n";
    // }

    // print_two_trees(tree1, tree2);
    // tree1.swap(tree2);
    // std::cout << "\nAfter Swapping:\n\n";
    // print_two_trees(tree1, tree2);

    // tree1.print();

    ft::map<int, int> map1, map2;

    for (int i = 1; i < 15; ++i) {
        map1.insert(ft::make_pair<const int, int>(i, i));
    }
    for (int i = 15; i < 30; ++i) {
        map2.insert(ft::make_pair<const int, int>(i, i));
    }
    std::cout << "Before Swapping:\n\n";
    compare_two_maps(map1, map2);
    map1.swap(map2);
    std::cout << "\nAfter Swapping:\n\n";
    compare_two_maps(map1, map2);
    return (0);
}
