/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:30:36 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 09:53:36 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <fucntional>
# include <algorithm>
# include <map>
# include "utils/less.hpp"

namespace ft {
	template <class Key,
			  class T,
			  class Compare = ft::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> >
		class map {
			public:


		};
}


#endif