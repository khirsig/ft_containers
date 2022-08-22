/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:02:30 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 09:04:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

int main() {
    // #ifdef TEST
    //     std::cout << "This is the ft container.\n";
    // #else
    //     std::cout << "This is the std container.\n";
    // #endif

#ifdef MAP
    map_tests();
#endif

#ifdef VECTOR
    vector_tests();
#endif
    return (0);
}