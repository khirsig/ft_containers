/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:14:46 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/13 12:02:11 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft {
	template<typename T>
	class vector_iterator {
		public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef value_type&			reference;

			vector_iterator(T *ptr)
				: _ptr(ptr) { }

			~vector_iterator() { }

			vector_iterator	&operator++()
			{
				++_ptr;
				return (*this);
			}

			vector_iterator	&operator++(int)
			{
				vector_iterator	*tmp = _ptr;
				++_ptr;
				return (tmp);
			}

			vector_iterator	&operator--()
			{
				--_ptr;
				return (*this);
			}

			vector_iterator	&operator--(int)
			{
				vector_iterator	*tmp = _ptr;
				--_ptr;
				return (tmp);
			}

			reference	operator[](int index)
			{
				return *(_ptr + index);
			}

			pointer	operator->()
			{
				return (_ptr);
			}

			reference	operator*()
			{
				return (*_ptr);
			}

			bool	operator==(const vector_iterator &other) const
			{
				return (_ptr == other._ptr);
			}

			bool	operator!=(const vector_iterator &other) const
			{
				return !(*this == other);
			}

			template<typename U>
				friend int	operator-(const vector_iterator<U> &pre, const vector_iterator<U> &post);
			template<typename U>
				friend vector_iterator<U>	operator+(const vector_iterator<U> &pre, const int &post);
			template<typename U>
				friend vector_iterator<U>	operator-(const vector_iterator<U> &pre, const int &post);
		private:
			pointer _ptr;
	};

	template<typename U>
	int	operator-(const vector_iterator<U> &pre, const vector_iterator<U> &post)
	{
		int	result;

		result = pre._ptr - post._ptr;
		return (result);
	}

	template<typename U>
	vector_iterator<U>	operator+(const vector_iterator<U> &pre, const int &post)
	{
		U	*result;

		result = pre._ptr + post;
		return (result);
	}

	template<typename U>
	vector_iterator<U>	operator-(const vector_iterator<U> &pre, const int &post)
	{
		U	*result;

		result = pre._ptr - post;
		return (result);
	}
}

#endif