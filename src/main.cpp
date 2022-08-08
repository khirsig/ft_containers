/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/08 16:00:30 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

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
    ft::node<int>          *save[3];
    for (int i = 1; i < 15; ++i) {
        system("clear");
        ft::node<int> *tmp = new ft::node<int>(i);
        if (i == 4) save[0] = tmp;
        if (i == 7) save[1] = tmp;
        if (i == 11) save[2] = tmp;
        tree.insert(tmp);
        tree.print();
        sleep(2);
    }
    // for (int i = 0; i < 3; ++i) {
    //     system("clear");
    //     tree.destroy(save[i]);
    //     tree.print();
    //     sleep(2);
    // }

    return (0);
}
