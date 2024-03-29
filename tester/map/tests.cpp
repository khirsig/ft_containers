/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 09:47:51 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void tests() {
    debug_padding("MAP TESTING", 50, '-');

    debug_padding("Constructors", 40, '=');
    {
        intmap m1;
        intmap m2(m1);

        m1.insert(NAMESPACE::make_pair(4, 4));
        m1.insert(NAMESPACE::make_pair(12, 14));
        m1.insert(NAMESPACE::make_pair(3, 4));
        print_all(m1, "m1");
        print_all(m2, "m2");

        intmap m3(m1.begin(), m1.end());
        print_all(m3, "m3");
    }
    debug_padding("", 40, '=');

    debug_padding("Assignment Operator", 40, '=');
    {
        strmap m1;

        m1.insert(NAMESPACE::make_pair("Michael Jordan", "Michael Jordan"));
        m1.insert(NAMESPACE::make_pair("LeBron James", "LeBron James"));
        m1.insert(NAMESPACE::make_pair("Kevin Durant", "Kevin Durant"));

        strmap m2 = m1;
        strmap m3;

        m3.insert(NAMESPACE::make_pair("Steph Curry", "Steph Curry"));
        m3.insert(NAMESPACE::make_pair("James Harden", "James Harden"));

        m3 = m2;

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");
    }
    debug_padding("", 40, '=');

    debug_padding("Iterators", 40, '=');
    {
        intmap m1;
        for (int i = 0; i < 4; ++i) {
            m1.insert(NAMESPACE::make_pair(i, i));
        }
        print_all(m1, "m1");

        intmap::iterator it = m1.begin();
        ++it;
        ++it;
        m1.erase(it);
        print_all(m1, "m1");

        m1.insert(NAMESPACE::make_pair(22, 3));
        m1.insert(NAMESPACE::make_pair(-22, 3));
        m1.insert(NAMESPACE::make_pair(21, 3));
        print_all_reverse(m1, "m1 reverse");

        intmap::const_iterator cit = m1.begin();
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
        intmap m1;

        for (std::size_t i = 0; i < 30; ++i) {
            m1.insert(NAMESPACE::make_pair(i * 2, i * 5));
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
        intmap m2 = m1;
        intmap m3(m1);

        print_size(m2);
        print_size(m3);

        m2.clear();
    }
    debug_padding("", 40, '=');

    debug_padding("at & operator[]", 40, '=');
    {
        intmap m1;

        for (std::size_t i = 0; i < 30; ++i)
            m1.insert(NAMESPACE::make_pair(i * 2, i * 5));

        for (intmap::size_type i = 0; i < 10; ++i)
            std::cout << "V: " << m1[i] << " | ";
        std::cout << "\n";

        for (intmap::size_type i = 0; i < 10; ++i)
            std::cout << "V: " << m1.at(i) << " | ";
        std::cout << "\n";

        try {
            m1[200] = 22;
        } catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << "\n";
        }

        for (intmap::size_type i = 0; i < 10; ++i) {
            m1[i] = 42;
        }
        print_all(m1, "m1");
    }
    debug_padding("", 40, '=');

    debug_padding("insert, erase & swap", 40, '=');
    {
        intmap m1;
        for (std::size_t i = 0; i < 30; ++i)
            m1.insert(NAMESPACE::make_pair(i * 2, i * 5));

        intmap m2;
        m2.insert(m1.begin(), m1.end());

        intmap m3(m2);
        m3.insert(m3.begin(), NAMESPACE::make_pair(23, 23));

        print_all(m1, "m1");
        print_all(m2, "m2");
        print_all(m3, "m3");

        m3.erase(23);
        for (intmap::size_type i = 0; i < 15; ++i) {
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
        intmap m1;
        for (std::size_t i = 0; i < 10; ++i)
            m1.insert(NAMESPACE::make_pair(i, i * 3));

        intmap::iterator it = m1.find(3);
        if (it != m1.end())
            print_one(it);
        else
            std::cout << "Warning: trying to print end()\n";

        it = m1.find(33);
        if (it != m1.end())
            print_one(it);
        else
            std::cout << "Warning: trying to print end()\n";

        intmap::const_iterator cit = m1.lower_bound(4);
        print_one(cit);
        cit = m1.upper_bound(4);
        print_one(cit);
    }
    debug_padding("", 40, '=');

    debug_padding("comparisons", 40, '=');
    {
        intmap m1;
        for (std::size_t i = 0; i < 10; ++i)
            m1.insert(NAMESPACE::make_pair(i, i * 3));
        intmap m2(m1);
        comparison_operators(m1, m2, "m1", "m2");

        m1.insert(NAMESPACE::make_pair(42, 42));
        comparison_operators(m1, m2, "m1", "m2");

        m1.insert(NAMESPACE::make_pair(42, 42));
        m2.insert(NAMESPACE::make_pair(43, 42));
        comparison_operators(m1, m2, "m1", "m2");
    }
    debug_padding("", 40, '=');

    debug_padding("", 50, '-');
}