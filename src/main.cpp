/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/13 09:44:16 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include <vector>
#include <iostream>

int	main()
{
	ft::vector<int> test;

	if (test.empty())
		std::cout << "Vector is empty with size " << test.size() << "\n";
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	test.reserve(5);
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	for (int i = 0; i < 5; ++i)
		test.push_back(i + 1);
	test.resize(10, 42);
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	std::cout << "Print all ints:" << "\n";
	for (int i = 0; i < 10; ++i)
		std::cout << test[i] << " ";
	std::cout << "\n";
	test.pop_back();
	test.pop_back();
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	if (!test.empty())
		std::cout << "Vector is not empty with size " << test.size() << "\n";
	std::cout << "Vector max_size = " << test.max_size() << "\n";

	return (0);
}
