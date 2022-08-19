/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 11:41:57 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void vector_tests() {

    debug_padding("VECTOR TESTING", 50, '-');

    debug_padding("Constructors", 40, '=');
    {

        intvec v1;
        print_all(v1, "v1");

        intvec v2(v1);
        print_all(v2, "v2");

        intvec v3(5, 22);
        print_all(v3, "v3");

        intvec v4(v3.begin(), v3.end());
        print_all(v4, "v4");

    }
    debug_padding("", 40, '=');

    debug_padding("Assignment Operator", 40, '=');
    {
        intvec v1(11, 5);
        intvec v2 = v1;
        intvec v3;
        v1 = v3;

        print_all(v1, "v1");
        print_all(v2, "v2");
        print_all(v3, "v3");
    }
    debug_padding("", 40, '=');

    debug_padding("Iterators", 40, '=');
    {
        intvec v1(12, 42);
        const intvec v2(v1);

        intvec::iterator it1 = v1.begin();
        intvec::iterator it2 = v1.end();
        std::cout << "\n";
        while (it1 != it2) {
            std::cout << "iterating through: " << *it1 << "\n";
            ++it1;
        }
        intvec::const_iterator it3 = v2.begin();
        std::cout << "begin: " << *it3 << "\n";

        intvec::reverse_iterator it4 = v1.rbegin();
        std::cout << "rbegin: " << *it4 << "\n";
        *it4 = 12;
        *v1.begin() = 11;

        print_all(v1, "v1");
    }
    debug_padding("", 40, '=');

    debug_padding("push_back, resize & reserve", 40, '=');
    {
        intvec v1;

        for (int i = 0; i < 10; ++i) {
            v1.push_back(i);
        }
        print_all(v1, "v1");

        v1.resize(6);
        print_all(v1, "v1");

        v1.reserve(35);
        print_all(v1, "v1");

        for (int i = 10; i < 20; ++i) {
            v1.push_back(i);
        }
        v1.resize(10);
        print_all(v1, "v1");

        v1.resize(0);
        v1.reserve(1);
        print_all(v1, "v1");
    }
    debug_padding("", 40, '=');

    debug_padding("pop_back, erase & clear", 40, '=');
    {
        intvec v1;

        for (int i = 0; i < 20; ++i) {
            v1.push_back(i);
        }
        print_all(v1, "v1");

        v1.pop_back();
        print_all(v1, "v1");

        v1.pop_back();
        v1.pop_back();
        print_all(v1, "v1");

        v1.erase(v1.begin());
        print_all(v1, "v1");

        v1.erase(v1.begin() + 2, v1.begin() + 5);
        print_all(v1, "v1");

        v1.clear();
        print_all(v1, "v1");
    }
    debug_padding("", 40, '=');

    debug_padding("assign & swap", 40, '=');
    {
        intvec v1;
        for (int i = 0; i < 20; ++i) {
            v1.push_back(i);
        }
        print_all(v1, "v1");

        intvec v2(v1);
        v1.assign(12, 42);
        print_all(v1, "v1");
        print_all(v2, "v2");

        v1.swap(v2);
        print_all(v1, "v1");
        print_all(v2, "v2");
    }
    debug_padding("", 40, '=');

    debug_padding("insert", 40, '=');
    {
        intvec v1;
        for (int i = 0; i < 20; ++i) {
            v1.push_back(i);
        }
        print_all(v1, "v1");

        v1.insert(v1.begin() + 7, 42);
        print_all(v1, "v1");

        intvec v2(6, 99);
        v1.insert(v1.begin() + 3, v2.begin(), v2.end());
        print_all(v1, "v1");

        v1.insert(v1.begin() + 12, 2, 88);
        print_all(v1, "v1");
    }
    debug_padding("", 40, '=');

    debug_padding("", 50, '-');

}