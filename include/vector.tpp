/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:28:37 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/12 08:54:46 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename type>
ft::vector<type>::vector()
{
	this->_content = NULL;
	this->_size = 0;
}

template <typename type>
ft::vector<type>::vector(const ft::vector<type> &other)
{
	*this = other;
}

template <typename type>
ft::vector<type>::~vector()
{
	delete (this->_content);
}

template <typename type>
ft::vector<type>	&ft::vector<type>::operator=(const ft::vector<type> &other)
{
	if (this->_size > 0)
		delete (this->_content);
	this->_size = other.size();
	if (this->_size > 0)
	{
		this->_content = new type[this->_size]();
		for (int i = 0; i < this->_size; ++i)
			this->_content[i] = other._content[i];
	}
	else
		this->_content = NULL;

	return (*this);
}

template <typename type>
type	&ft::vector<type>::operator[](int i)
{
	if (this->_size <= 0 || i >= this->_size || i < 0)
		throw (ft::vector<type>::NotAllocatedException());
	return (this->_content[i]);
}

template <typename type>
int		ft::vector<type>::size() const
{
	return (this->_size);
}

template <typename type>
const char *ft::vector<type>::NotAllocatedException::what() const throw()
{
	return ("Memory tried to access is out of bounds.");
}
