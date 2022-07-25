/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:06:19 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/25 09:31:24 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include <vector>
#include <iostream>

#ifdef TEST
# define J 1
# define VEC ft::vector<int>
# define NS ft
#else
# define J 0
# define VEC std::vector<int>
# define NS std
#endif

int	main()
{
	VEC test;

	if (J)
		std::cout << "This is my vector.\n\n";
	else
		std::cout << "This is the standard vector.\n\n";

	if (test.empty())
		std::cout << "Vector is empty with size " << test.size() << "\n";
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	test.reserve(5);
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	for (std::size_t i = 0; i < test.capacity(); ++i)
		test.push_back(i + 1);
	test.resize(10, 42);
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";
	std::cout << "Print all ints:" << "\n";
	for (std::size_t i = 0; i < test.size(); ++i)
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
	std::cout << "Front: " << test.front() << "\n" << "Back: " << test.back() << "\n";


	VEC	cpy;

	cpy.assign(test.begin(), test.end());
	std::cout << "Size: " << cpy.size() << "  Capacity: " << cpy.capacity() << "\n";

	for (VEC::iterator i = cpy.begin(); i != cpy.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";
	cpy.insert(cpy.begin() + 2, 23);
	for (std::size_t i = 0; i < cpy.size(); ++i)
		std::cout << cpy[i] << " ";
	std::cout << "\n";
	std::cout << "Size: " << cpy.size() << "  Capacity: " << cpy.capacity() << "\n";
	cpy.insert(cpy.begin() + 4, 3, 10);
	std::cout << "Size: " << cpy.size() << "  Capacity: " << cpy.capacity() << "\n";
	for (std::size_t i = 0; i < cpy.size(); ++i)
		std::cout << cpy[i] << " ";
	std::cout << "\n";
	cpy.erase(cpy.begin() + 3);
	std::cout << "Size: " << cpy.size() << "  Capacity: " << cpy.capacity() << "\n";
	for (std::size_t i = 0; i < cpy.size(); ++i)
		std::cout << cpy[i] << " ";
	std::cout << "\n";
	cpy.erase(cpy.begin() + 2, cpy.begin() + 5);
	std::cout << "Size: " << cpy.size() << "  Capacity: " << cpy.capacity() << "\n";
	for (std::size_t i = 0; i < cpy.size(); ++i)
		std::cout << cpy[i] << " ";
	std::cout << "\n";
	cpy.swap(test);
	std::cout << "Cpy after Swap: ";
	for (std::size_t i = 0; i < cpy.size(); ++i)
		std::cout << cpy[i] << " ";
	std::cout << "Test after Swap: ";
	for (std::size_t i = 0; i < test.size(); ++i)
		std::cout << test[i] << " ";
	std::cout << "\n";
	test.clear();
	std::cout << "Test after clear: ";
	for (std::size_t i = 0; i < test.size(); ++i)
		std::cout << test[i] << " ";
	std::cout << "\n";
	std::cout << "Size: " << test.size() << "  Capacity: " << test.capacity() << "\n";

	if (NS::is_integral<char>::value)
		std::cout << "Char is integral\n";
	if (!NS::is_integral<float>::value)
		std::cout << "Float is not integral\n";
	if (NS::equal(test.begin(), test.end(), cpy.begin()))
		std::cout << "Cpy and Test are equal.\n";
	if (NS::lexicographical_compare(test.begin(), test.end(), cpy.begin(), cpy.end()))
		std::cout << "Lexicographical_compare is true.\n";

	ft::pair<std::string,VEC> tar;
	return (0);
}
