/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/08 11:01:20 by khirsig          ###   ########.fr       */
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
    std::vector<int> t;
    srand(time(NULL));
    ft::red_black_tree<int> tree;
    for (int i = 0; i < 50; ++i) {
        system("clear");
        int j = rand() % 1000;
        ft::node<int> *tmp = new ft::node<int>(j);
        tree.insert(tmp);
        tree.print();
        usleep(50000);
    }
    system("clear");
    tree.print();
    return (0);
}
