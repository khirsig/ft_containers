/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:14:46 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/26 09:41:25 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft {
	template <typename T>
	class vector_iterator {
		public:
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			vector_iterator(T *ptr)
				: _ptr(ptr) { }

			~vector_iterator() { }

			vector_iterator	&operator++()
			{
				++_ptr;
				return (*this);
			}

			vector_iterator	operator++(int)
			{
				pointer	tmp = _ptr;
				++_ptr;
				return vector_iterator(tmp);
			}

			vector_iterator	&operator--()
			{
				--_ptr;
				return (*this);
			}

			vector_iterator	operator--(int)
			{
				pointer	tmp = _ptr;
				--_ptr;
				return vector_iterator(tmp);
			}

    		operator	vector_iterator<const T>() const
			{
				return (vector_iterator<const T>(this->_ptr));
			}

			reference	operator[](int index) { return *(_ptr + index); }

			pointer	operator->() { return (_ptr); }

			reference	operator*() { return (*_ptr); }

			bool	operator==(const vector_iterator &other) const
				{ return (_ptr == other._ptr); }

			bool	operator!=(const vector_iterator &other) const
				{ return !(*this == other); }

			template<typename U>
				friend int	operator+(const vector_iterator<U> &pre, const vector_iterator<U> &post);
			template<typename U>
				friend int	operator-(const vector_iterator<U> &pre, const vector_iterator<U> &post);
			template<typename U>
				friend vector_iterator<U>	operator+(const vector_iterator<U> &pre, const int &post);
			template<typename U>
				friend vector_iterator<U>	operator-(const vector_iterator<U> &pre, const int &post);
		protected:
			pointer _ptr;
	};

	template <typename T>
	class vector_reverse_iterator : public vector_iterator<T> {
		public:
			typedef T					value_type;
			typedef value_type*			pointer;
			typedef value_type&			reference;

			vector_reverse_iterator	&operator++()
			{
				--this->_ptr;
				return (*this);
			}

			vector_reverse_iterator	operator++(int)
			{
				pointer	tmp = this->_ptr;
				--this->_ptr;
				return vector_reverse_iterator(tmp);
			}

			vector_reverse_iterator	&operator--()
			{
				++this->_ptr;
				return (*this);
			}

			vector_reverse_iterator	operator--(int)
			{
				pointer	tmp = this->_ptr;
				++this->_ptr;
				return vector_reverse_iterator(tmp);
			}
	};

	template <typename U>
	int	operator+(const vector_iterator<U> &pre, const vector_iterator<U> &post)
	{
		int	result;

		result = pre._ptr + post._ptr;
		return (result);
	}

	template <typename U>
	int	operator-(const vector_iterator<U> &pre, const vector_iterator<U> &post)
	{
		int	result;

		result = pre._ptr - post._ptr;
		return (result);
	}

	template <typename U>
	vector_iterator<U>	operator+(const vector_iterator<U> &pre, const int &post)
	{
		U	*result;

		result = pre._ptr + post;
		return (result);
	}

	template <typename U>
	vector_iterator<U>	operator-(const vector_iterator<U> &pre, const int &post)
	{
		U	*result;

		result = pre._ptr - post;
		return (result);
	}

	template <class InputIt>
	typename vector_iterator<InputIt>::difference_type	distance(InputIt first, InputIt last)
	{
		typename vector_iterator<InputIt>::difference_type	dist = 0;
		while (first != last)
			++first, ++dist;
		return	dist;
	}
}

#endif