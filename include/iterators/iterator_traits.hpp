/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:22:08 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/26 09:01:50 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bitdirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bitdirectional_iterator_tag { };

	template <class Iterator>
	class iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*> {
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};
}

#endif