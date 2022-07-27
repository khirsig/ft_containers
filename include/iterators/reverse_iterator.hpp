/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:27:15 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/27 13:49:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"

namespace ft {
	template <class Iterator>
		class reverse_iterator {
			public:
				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::value_type			value_type;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;

				reverse_iterator()
					: _current() { }

				explicit reverse_iterator(iterator_type it)
					: _current(it) { }

				template <class Iter>
				reverse_iterator(const reverse_iterator<Iter> &rev_it)
					: _current(rev_it.base()) { }

				~reverse_iterator() { }

				iterator_type	base() const { return (_current); }

				reference	operator*() const { iterator_type tmp = _current; return *(--tmp); }

				reverse_iterator	&operator++()
				{
					_current--;
					return (*this);
				}

				reverse_iterator	operator++(int)
				{
					reverse_iterator	tmp = *this;
					--_current;
					return (tmp);
				}

				reverse_iterator	&operator--()
				{
					_current++;
					return (*this);
				}

				reverse_iterator	operator--(int)
				{
					reverse_iterator	tmp = *this;
					++_current;
					return (tmp);
				}

				reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_current - n); }

				reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_current + n); }

				reverse_iterator	&operator+=(difference_type n) { _current -= n; return (*this); }

				reverse_iterator	&operator-=(difference_type n) { _current += n; return (*this); }

				pointer	operator->() const { return (_current.base()); }

				reference	operator[](difference_type n) { return *(_current + n); }

			private:
				iterator_type	_current;
		};

	template <class Iterator1, class Iterator2>
		bool	operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator1, class Iterator2>
		bool	operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return !(lhs.base() == rhs.base());
		}

	template <class Iterator1, class Iterator2>
		bool	operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator1, class Iterator2>
		bool	operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class Iterator1, class Iterator2>
		bool	operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator1, class Iterator2>
		bool	operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator>
		reverse_iterator<Iterator>	operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &rev_it)
		{
			return reverse_iterator<Iterator>(rev_it.base() + n);
		}

	template <class Iterator1, class Iterator2>
		typename reverse_iterator<Iterator1>::difference_type	operator-(
			const reverse_iterator<Iterator1> &lhs,
			const reverse_iterator<Iterator2> &rhs)
		{
			return typename reverse_iterator<Iterator1>::difference_type(lhs.base() - rhs.base());
		}
}

#endif