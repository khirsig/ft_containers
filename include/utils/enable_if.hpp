/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:38:46 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/21 11:55:36 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF
# define ENABLE_IF

namespace ft {
	template <bool, typename _Tp = void>
	struct enable_if { };

	template <typename _Tp>
	struct enable_if<true, _Tp> {
		typedef _Tp	type;
	};
}

#endif