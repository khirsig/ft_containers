/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:47:21 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/28 09:53:08 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
# define LESS_HPP

namespace ft {
	template <class T>
		struct less : binary_function <T, T, bool> {
			bool	operator()(const T &x, const T &y) const
			{
				return (x < y);
			}
		};
}

#endif