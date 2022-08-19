/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:13 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 11:50:28 by khirsig          ###   ########.fr       */
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

    debug_padding("", 50, '-');

}