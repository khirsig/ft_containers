/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:22:39 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/14 15:31:18 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef>
# include <exception>
# include <memory>
# include <stdexcept>
# include "vector_iterator.hpp"

namespace ft {
	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
		public:
			// Typedefs
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef ft::vector_iterator<T>						iterator;

			// Construct/Copy/Destroy
			vector() : _content(NULL), _size(0), _capacity(0) { }

			vector(const vector<value_type> &other)
				: _content(other._content),
				  _size(other._size),
				  _capacity(other._capacity) { }

			~vector() { }

			// Operators
			vector		&operator=(const vector &other);

			value_type	&operator[](unsigned int i) { return (_content[i]); }

			// Iterators
			iterator	begin() const { return (_content); }

			iterator	end() const { return (_content + _size); }

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
					throw std::out_of_range("Error: Element trying to access is out of range.");
				return (*(_content + n));
			}

			reference	front() { return (*(_content)); }

			reference	back() { return (*(_content + _size)); }

			// Modifiers
			void	assign(iterator first, iterator last)
			{
				size_type n = last - first;
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
					_allocator.construct(_content + i, *(first + i));
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
				int	savedPos = position - begin();
				if (_size + 1 >= _capacity)
					reserve(_capacity * 2);
				int i = size();

				while (i > savedPos)
				{
					_allocator.construct(_content + i, *(_content + i - 1));
					_allocator.destroy(_content + i - 1);
					--i;
				}
				_allocator.construct(_content + i, val);
				++_size;
				return (iterator(_content + i));
			}

			iterator	insert(iterator position, size_type n, const value_type &val)
			{
				int	savedPos = position - begin();
				if (_size + n >= _capacity)
				{
					size_type	new_cap = _capacity * 2;
					while (new_cap < n)
						new_cap *= 2;

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
				return (iterator(_content + i));
			}

			// template <class InputIterator>
			// void	insert(iterator position, InputIterator first, InputIterator last)
			// {
			// 	int	savedPos = position - begin();
			// 	size_type	n = last - first;
			// 	if (_size + n >= _capacity)
			// 	{
			// 		size_type	new_cap = _capacity * 2;
			// 		while (new_cap < n)
			// 			new_cap *= 2;

			// 		reserve(new_cap);
			// 	}
			// 	int i = size() + n;
			// 	while (i >= (int)(savedPos + n))
			// 	{
			// 		_allocator.construct(_content + i, *(_content + i - n));
			// 		_allocator.destroy(_content + i - n);
			// 		--i;
			// 	}
			// 	--last;
			// 	// int j = n;
			// 	while (i >= savedPos)
			// 	{
			// 		_allocator.construct(_content + i, last);
			// 		--last;
			// 		--i;
			// 	}
			// 	_size += n;
			// }

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
		private:
			pointer			_content;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
	};
}

#endif
