/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:22:39 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/12 16:08:22 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef>
# include <exception>
# include <memory>
# include <stdexcept>

namespace ft {
	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
		public:
			// Typedefs
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef pointer										iterator;

			// Construct/Copy/Destroy
			vector() : _content(NULL), _size(0), _capacity(0) { }

			vector(const vector<value_type> &other)
				: _content(other._content),
				  _size(other._size),
				  _capacity(other._capacity)
			{ }

			~vector() { }

			// Operators
			vector		&operator=(const vector &other);

			value_type	&operator[](unsigned int i)
			{
				return (this->_content[i]);
			}

			// Member functions
			size_type	size() const
			{
				return (this->_size);
			}

			size_type	capacity() const
			{
				return (this->_capacity);
			}

			iterator	begin() const
			{
				return (this->_content);
			}

			iterator	end() const
			{
				return (this->_content + (this->_size - 1));
			}

			void	reserve(size_type new_cap)
			{
				if (new_cap > capacity())
				{
					pointer	new_alloc = NULL;
					new_alloc = this->_allocator.allocate(new_cap);
					for (size_type i = 0; i < this->_size; ++i)
					{
						this->_allocator.construct(new_alloc + i, *(this->_content + i));
						this->_allocator.destroy(this->_content + i);
					}
					this->_allocator.deallocate(this->_content, this->_capacity);
					this->_capacity = new_cap;
					this->_content = new_alloc;
				}
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					pointer	new_alloc = NULL;
					new_alloc = this->_allocator.allocate(n);
					for (size_type i = 0; i < n; ++i)
					{
						this->_allocator.construct(new_alloc + i, *(this->_content + i));
						this->_allocator.destroy(this->_content + i);
					}
					for (size_type i = n; i < size(); ++i)
						this->_allocator.destroy(this->_content + i);
					this->_allocator.deallocate(this->_content, this->_capacity);
					this->_capacity = n;
					this->_size = n;
					this->_content = new_alloc;
				}
				else if (n > size() && n < capacity())
				{
					for (size_type i = size(); i < n; ++i)
						*(this->_content + i) = val;
					this->_size = n;
				}
				else if (n > capacity())
				{
					reserve(n);
					for (size_type i = size(); i < n; ++i)
						*(this->_content + i) = val;
					this->_size = n;
				}
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
				this->_size++;
				this->_allocator.construct(end(), value);
			}

		private:
			pointer			_content;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
	};
}

#endif