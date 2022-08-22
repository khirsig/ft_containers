/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 09:47:44 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void tests() {
    debug_padding("MAP TESTING", 50, '-');

    debug_padding("Constructors", 40, '=');
    {
        intset m1;
        intset m2(m1);

        m1.insert(4);
        m1.insert(14);
        m1.insert(3);
        print_all(m1, "m1");
        print_all(m2, "m2");

        intset m3(m1.begin(), m1.end());
        print_all(m3, "m3");
    }
    debug_padding("", 40, '=');

    debug_padding("Assignment Operator", 40, '=');
    {
        strset m1;

        m1.insert("Michael Jordan");
        m1.insert("LeBron James");
        m1.insert("Kevin Durant");

        strset m2 = m1;
        strset m3;

        m3.insert("Steph Curry");
        m3.insert("James Harden");

        m3 = m2;

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");
    }
    debug_padding("", 40, '=');

    debug_padding("Iterators", 40, '=');
    {
        intset m1;
        for (int i = 0; i < 4; ++i) {
            m1.insert(i);
        }
        print_all(m1, "m1");

        intset::iterator it = m1.begin();
        ++it;
        ++it;
        m1.erase(it);
        print_all(m1, "m1");

        m1.insert(22);
        m1.insert(-22);
        m1.insert(21);
        print_all_reverse(m1, "m1 reverse");

        intset::const_iterator cit = m1.begin();
        ++cit;
        print_one(cit);
        for (; cit != m1.end(); ++cit)
            continue;
        --cit;
        print_one(cit);
    }
    debug_padding("", 40, '=');

    debug_padding("empty, size, clear", 40, '=');
    {
        intset m1;

        for (std::size_t i = 0; i < 30; ++i) {
            m1.insert(i * 2);
        }
        print_all(m1, "m1");
        if (m1.empty()) {
            std::cout << "\nm1 is empty\n";
        }
        m1.clear();
        print_all(m1, "m1");
        if (m1.empty()) {
            std::cout << "\nm1 is empty\n";
        }
        intset m2 = m1;
        intset m3(m1);

        print_size(m2);
        print_size(m3);

        m2.clear();
    }
    debug_padding("", 40, '=');

    debug_padding("insert, erase & swap", 40, '=');
    {
        intset m1;
        for (std::size_t i = 0; i < 30; ++i)
            m1.insert(i * 2);

        intset m2;
        m2.insert(m1.begin(), m1.end());

        intset m3(m2);
        m3.insert(m3.begin(), 23);

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");

        m3.erase(23);
        for (intset::size_type i = 0; i < 15; ++i) {
            m2.erase(m2.begin());
        }
        m1.erase(m1.begin(), m1.end());

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");

        m1.swap(m2);
        m2.swap(m3);
        m3.swap(m1);

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");
    }
    debug_padding("", 40, '=');

    debug_padding("find & bounds", 40, '=');
    {
        intset m1;
        for (std::size_t i = 0; i < 10; ++i)
            m1.insert(i);

        intset::iterator it = m1.find(3);
        if (it != m1.end())
            print_one(it);
        else
            std::cout << "Warning: trying to print end()\n";

        it = m1.find(33);
        if (it != m1.end())
            print_one(it);
        else
            std::cout << "Warning: trying to print end()\n";

        intset::const_iterator cit = m1.lower_bound(4);
        print_one(cit);
        cit = m1.upper_bound(4);
        print_one(cit);
    }
    debug_padding("", 40, '=');

    debug_padding("comparisons", 40, '=');
    {
        intset m1;
        for (std::size_t i = 0; i < 10; ++i)
            m1.insert(i);
        intset m2(m1);
        comparison_operators(m1, m2, "m1", "m2");

        m1.insert(42);
        comparison_operators(m1, m2, "m1", "m2");

        m1.insert(42);
        m2.insert(43);
        comparison_operators(m1, m2, "m1", "m2");
    }
    debug_padding("", 40, '=');

    debug_padding("", 50, '-');
}