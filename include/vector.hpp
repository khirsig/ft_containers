/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:22:39 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/26 15:59:33 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef>
# include <exception>
# include <memory>
# include <stdexcept>
# include <utility>
# include "iterators/random_access_iterator.hpp"
# include "iterators/reverse_iterator.hpp"
# include "utils/is_integral.hpp"
# include "utils/enable_if.hpp"
# include "utils/equal.hpp"
# include "utils/make_pair.hpp"
# include "utils/lexicographical_compare.hpp"

namespace ft {
	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
		public:
			// Typedefs
			typedef T																value_type;
			typedef Allocator														allocator_type;
			typedef typename allocator_type::size_type								size_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef value_type*														pointer;
			typedef const value_type*												const_pointer;
			typedef typename random_access_iterator<value_type>::difference_type	difference_type;
			typedef random_access_iterator<value_type>								iterator;
			typedef random_access_iterator<const value_type>						const_iterator;
			typedef reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef reverse_iterator<iterator>										reverse_iterator;

			// Construct/Copy/Destroy
			explicit vector(const allocator_type &alloc = allocator_type()) : _content(NULL), _size(0), _capacity(0)
			{
				_allocator = alloc;
			}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				_allocator = alloc;
				_content = _allocator.allocate(n);
				for (size_t i = 0; i < n; i++)
					_allocator.construct(_content + i, val);
				_size = n;
				_capacity = n;
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0)
			{
				_allocator = alloc;
				_capacity = 0;
				_size = 0;
				assign(first, last);
			}

			vector(const vector<value_type> &other)
				: _content(NULL),
				  _size(0),
				  _capacity(0),
				  _allocator()
			{
				*this = other;
			}

			~vector() { }

			// Operators
			vector		&operator=(const vector &other)
			{
				size_type n = other.size();
				for (size_type i = 0; i < size(); ++i)
					_allocator.destroy(_content + i);
				if (n > _capacity)
				{
					if (_capacity > 0)
						_allocator.deallocate(_content, _capacity);
					_content = _allocator.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; ++i)
					_allocator.construct(_content + i, *(other.begin() + i));
				_size = n;
				return (*this);
			}

			value_type	&operator[](unsigned int i) { return (_content[i]); }

			// Iterators
			iterator	begin() { return (_content); }

			const_iterator	begin() const { return (_content); }

			iterator	end() { return (_content + _size); }

			const_iterator	end() const { return (_content + _size); }

			reverse_iterator	rbegin() { return reverse_iterator(_content + _size); }

			const_reverse_iterator	rbegin() const { return const_reverse_iterator(_content + _size); }

			reverse_iterator	rend() { return reverse_iterator(_content); }

			const_reverse_iterator	rend() const { return const_reverse_iterator(_content); }

			// Capacity
			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_allocator.max_size()); }

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					pointer	new_alloc = NULL;
					new_alloc = _allocator.allocate(n);
					for (size_type i = 0; i < n; ++i)
					{
						_allocator.construct(new_alloc + i, *(_content + i));
						_allocator.destroy(_content + i);
					}
					for (size_type i = n; i < size(); ++i)
						_allocator.destroy(_content + i);
					_allocator.deallocate(_content, _capacity);
					_capacity = n;
					_size = n;
					_content = new_alloc;
				}
				else if (n > size() && n < capacity())
				{
					for (size_type i = size(); i < n; ++i)
						*(_content + i) = val;
					_size = n;
				}
				else if (n > capacity())
				{
					reserve(n);
					for (size_type i = size(); i < n; ++i)
						*(_content + i) = val;
					_size = n;
				}
			}

			size_type	capacity() const { return (_capacity); }

			bool	empty() const { return (_size == 0 ? true : false); }

			void	reserve(size_type new_cap)
			{
				if (new_cap > capacity())
				{
					pointer	new_alloc = NULL;
					new_alloc = _allocator.allocate(new_cap);
					for (size_type i = 0; i < _size; ++i)
					{
						_allocator.construct(new_alloc + i, *(_content + i));
						_allocator.destroy(_content + i);
					}
					_allocator.deallocate(_content, _capacity);
					_capacity = new_cap;
					_content = new_alloc;
				}
			}

			// Element Access
			reference	at(size_type n)
			{
				if (n > _size)
					throw std::out_of_range("vector");
				return (*(_content + n));
			}

			const_reference	at(size_type n) const
			{
				if (n > _size)
					throw std::out_of_range("vector");
				return (*(_content + n));
			}

			reference	front() { return (*(_content)); }

			const_reference	front() const { return (*(_content)); }

			reference	back() { return (*(_content + _size - 1)); }

			const_reference	back() const { return (*(_content + _size - 1)); }

			// Modifiers
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
					typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0)
			{
				size_type n = (size_type)ft::distance(first, last);
				for (size_type i = 0; i < size(); ++i)
					_allocator.destroy(_content + i);
				if (n > _capacity)
				{
					if (_capacity > 0)
						_allocator.deallocate(_content, _capacity);
					_content = _allocator.allocate(n);
					_capacity = n;
				}

				for (size_type i = 0; first != last; ++first, ++i)
					_allocator.construct(_content + i, *first);
				_size = n;
			}

			void	assign(size_type n, const value_type &val)
			{
				for (size_type i = 0; i < size(); ++i)
					_allocator.destroy(_content + i);
				if (n > _capacity)
				{
					_allocator.deallocate(_content, _capacity);
					_content = _allocator.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; ++i)
					_allocator.construct(_content + i, val);
				_size = n;
			}

			void	push_back(const T &value)
			{
				if (size() + 1 > capacity())
				{
					if (capacity() == 0)
						reserve(1);
					else
						reserve(capacity() * 2);
				}
				_allocator.construct(_content + _size, value);
				++_size;
			}

			void	pop_back()
			{
				_allocator.destroy(_content + _size - 1);
				--_size;
			}

			iterator	insert(iterator position, const value_type &val)
			{
				insert(position, 1, val);
				return (_content + (position - begin()));
			}

			void	insert(iterator position, size_type n, const value_type &val)
			{
				int	savedPos = position - begin();
				if (_size + n >= _capacity)
				{
					size_type	new_cap = _capacity;
					if (new_cap == 0)
						new_cap = 1;
					if (new_cap < n + _size)
						new_cap *= 2;
					if (new_cap < n + _size)
						new_cap = n + _size;

					reserve(new_cap);
				}
				int i = size() + n;
				while (i >= (int)(savedPos + n))
				{
					_allocator.construct(_content + i, *(_content + i - n));
					_allocator.destroy(_content + i - n);
					--i;
				}
				while (i >= savedPos)
				{
					_allocator.construct(_content + i, val);
					--i;
				}
				_size += n;
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0)
			{
				int	savedPos = position - begin();
				size_type	n = (size_type)ft::distance(first, last);
				if (_size + n >= _capacity)
				{
					size_type new_cap = _capacity;
					if (new_cap == 0)
						new_cap = 1;
					if (new_cap < n + _size)
						new_cap *= 2;
					if (new_cap < n + _size)
						new_cap = n + _size;

					reserve(new_cap);
				}
				int i = size() + n;
				while (i >= (int)(savedPos + n))
				{
					_allocator.construct(_content + i, *(_content + i - n));
					_allocator.destroy(_content + i - n);
					--i;
				}
				--last;
				// int j = n;
				while (i >= savedPos)
				{
					_allocator.construct(_content + i, *last);
					--last;
					--i;
				}
				_size += n;
			}

			iterator erase(iterator position)
			{
				size_type savedPos = position - begin();
				for (size_type i = savedPos; i < _size - 1; ++i)
				{
					_allocator.destroy(_content + i);
					_allocator.construct(_content + i, *(_content + i + 1));
				}
				--_size;
				return (_content + savedPos);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type	savedPos = first - begin();
				size_type	n = last - first;
				for (size_type i = savedPos; i < _size - n; ++i)
				{
					_allocator.destroy(_content + i);
					_allocator.construct(_content + i, *(_content + i + n));
				}
				_size -= n;
				return (begin() + savedPos);
			}

			void	swap(vector &x)
			{
				allocator_type tmp_al = _allocator;
				pointer	tmp_cnt = _content;
				size_type tmp_size = _size;
				size_type tmp_cap = _capacity;

				_allocator = x._allocator;
				_content = x._content;
				_size = x._size;
				_capacity = x._capacity;
				x._allocator = tmp_al;
				x._content = tmp_cnt;
				x._size = tmp_size;
				x._capacity = tmp_cap;
			}

			void	clear()
			{
				for (size_type i = 0; i < size(); ++i)
					_allocator.destroy(_content + i);
				_size = 0;
			}

			allocator_type	get_allocator() const
			{
				return (_allocator);
			}
		private:
			pointer			_content;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
	};

	template <typename T, typename Allocator>
	bool	operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename T, typename Allocator>
	bool	operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Allocator>
	bool	operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Allocator>
	bool	operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Allocator>
	bool	operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Allocator>
	bool	operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
	{
		return (rhs < lhs);
	}
}

#endif
