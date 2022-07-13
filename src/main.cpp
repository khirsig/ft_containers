/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/13 10:16:50 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include <vector>
#include <iostream>

int	main()
{
	ft::vector<int> test;
	// std::vector<int> test;

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

	int tmp = test.at(3);
	std::cout << "at(3) points to: " << tmp << "\n";
	try {
		std::cout << "at(42) points to: " << test.at(42) << "\n";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}

	return (0);
}
