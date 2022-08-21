/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/21 15:05:22 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void map_tests() {
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

    debug_padding("", 50, '-');
}