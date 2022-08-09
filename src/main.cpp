/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/09 10:37:09 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../include/iterators/tree_iterator.hpp"
#include "../include/trees/binary_search_tree.hpp"
#include "../include/trees/red_black_tree.hpp"

int main() {
    // std::vector<int> t;
    // srand(time(NULL));
    // ft::red_black_tree<int> tree;
    // for (int i = 0; i < 50; ++i) {
    //     system("clear");
    //     int j = rand() % 1000;
    //     ft::node<int> *tmp = new ft::node<int>(j);
    //     tree.insert(tmp);
    //     tree.print();
    //     usleep(50000);
    // }
    // system("clear");
    // tree.print();

    ft::red_black_tree<int> tree;
    for (int i = 1; i < 15; ++i) {
        ft::node<int> *tmp = new ft::node<int>(i);
        tree.insert(tmp);
    }
    for (ft::red_black_tree<int>::iterator it = tree.min(); it != tree.max(); ++it)
        std::cout << *it << "\n";

    // for (int i = 0; i < 3; ++i) {
    //     system("clear");
    //     tree.destroy(save[i]);
    //     tree.print();
    //     sleep(2);
    // }

    return (0);
}
