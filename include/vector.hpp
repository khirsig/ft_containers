/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:22:39 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/12 08:54:13 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <exception>

namespace ft {

template <typename type> class vector {
	public:
		vector();
		vector(const vector &other);
		~vector();

		vector	&operator=(const vector &other);
		type	&operator[](int i);

		int		size() const;
	private:
		type	*_content;
		int		_size;

	class NotAllocatedException : public std::exception {
		virtual const char *what() const throw();
	};
};

}

# include "vector.tpp"

#endif