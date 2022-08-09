/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/09 15:18:54 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../include/iterators/tree_iterator.hpp"
#include "../include/map.hpp"

template <class T>
void print_two_trees(ft::red_black_tree<T> &tree1, ft::red_black_tree<T> &tree2) {
    typename ft::red_black_tree<T>::iterator it1 = tree1.begin(), it2 = tree2.begin();
    while (it1 != tree1.end() && it2 != tree2.end()) {
        if (it1 != tree1.end()) {
            std::cout << *it1 << " ";
            ++it1;
        }
        if (it2 != tree2.end()) {
            std::cout << *it2 << "\n";
            ++it2;
        }
    }
    std::cout << *it1 << " " << *it2 << "\n";
}

int main() {
    // ft::red_black_tree<int> tree1, tree2;

    // for (int i = 1; i < 15; ++i)
    //     tree1.insert(i);
    // for (int i = 15; i < 30; ++i)
    //     tree2.insert(i);

    // print_two_trees(tree1, tree2);
    // tree1.swap(tree2);
    // std::cout << "\nAfter Swapping:\n\n";
    // print_two_trees(tree1, tree2);

    ft::map<int, int> test;

    return (0);
}
