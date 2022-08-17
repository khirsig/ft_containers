/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DebugBox.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:59:18 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/17 09:30:53 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_BOX_HPP_
#define DEBUG_BOX_HPP_

#include <cstdlib>
#include <string>
#include <iostream>


namespace ft {
	class DebugBox {
		public:
		DebugBox(const std::size_t width = 30);
		~DebugBox();

		void	padding(const std::string title) const;

		// template <typename T>
		// void	content(const T content) const;

		private:
		std::size_t _width;
	};
}

ft::DebugBox::DebugBox(const std::size_t width) : _width(width) {
	if (_width < 5)
		_width = 5;
}

ft::DebugBox::~DebugBox() {}

void	ft::DebugBox::padding(const std::string title) const {
    std::cout << "\n\n";
	std::string tmp(title);

    if (_width < tmp.length())
       tmp.resize(_width - 2);

    std::size_t filler = (_width - tmp.length()) / 2;
    std::size_t index = 0;

    for (; index < filler; ++index) {
        std::cout << "-";
    }
    std::cout << tmp;
    index += tmp.length();
    for (; index < _width; ++index) {
        std::cout << "-";
    }
    std::cout << "\n\n\n";
}


#endif