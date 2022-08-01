/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/01 14:38:53 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include "../include/trees/binary_search_tree.hpp"
#include "../include/trees/red_black_tree.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

int	main()
{
	ft::vector<int> t;

	t.push_back(5);
	t.push_back(5);
	t.push_back(5);
	t.push_back(5);

	ft::vector<int> t2(t);
	// srand(time(NULL));
	// ft::red_black_tree<int> tree;
	// for (int i = 0; i < 50; ++i)
	// {
	// 	int j = rand() % 1000;
	// 	ft::node<int> *tmp = new ft::node<int>(j);
	// 	tree.insert(tmp);
	// }
	// tree.print();
	return (0);
}
