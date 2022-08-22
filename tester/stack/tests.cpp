/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 10:21:03 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void tests() {
    debug_padding("STACK TESTING", 50, '-');
    {
        intstack s1;

        if (s1.empty())
            std::cout << "\ns1 is empty\n";
        else
            std::cout << "\ns1 is not empty\n";

        s1.push(5);
        if (s1.empty())
            std::cout << "\ns1 is empty\n";
        else
            std::cout << "\ns1 is not empty\n";
        std::cout << "\nTop: " << s1.top() << "\n";
        std::cout << "Size: " << s1.size() << "\n";
        for (std::size_t i = 0; i < 10; ++i)
            s1.push(i);
        std::cout << "\nTop: " << s1.top() << "\n";
        std::cout << "Size: " << s1.size() << "\n";
        std::cout << "Content: ";
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << s1.top() << " ";
            s1.pop();
        }
        std::cout << "\nTop: " << s1.top() << "\n";
        std::cout << "Size: " << s1.size() << "\n";
    }
    debug_padding("", 50, '-');
}
