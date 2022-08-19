/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:54 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/19 10:57:47 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void    debug_padding(std::string title, std::size_t width, char c) {
    std::cout << "\n";
    if (title.length() > width)
        title.resize(width - 2);
    std::size_t begin = (width - title.length()) / 2;
    std::size_t i = 0;

    for (; i < begin; ++i) {
        std::cout << c;
    }
    std::cout << title;
    i += title.length();
    for (; i < width; ++i) {
        std::cout << c;
    }
    std::cout << "\n";
}
