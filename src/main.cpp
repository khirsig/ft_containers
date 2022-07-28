/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 13:28:48 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include "../include/trees/binary_search_tree.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

int	main()
{
	srand(time(NULL));
	ft::binary_search_tree<int> tree;
	for (int i = 0; i < 20; ++i)
	{
		ft::node<int> *tmp = new ft::node<int>(rand() % 1000);
		tree.insert(tmp);
	}
	tree.print();
	return (0);
}
