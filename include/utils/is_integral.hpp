/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:40:31 by khirsig           #+#    #+#             */
/*   Updated: 2022/07/21 11:25:04 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL
# define IS_INTEGRAL

namespace ft {
	template <class T, T v>
	struct integral_constant {
		typedef T						value_type;
		typedef integral_constant<T,v>	type;

		static const T value = v;
		operator T() { return (v); }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T> struct is_integral : public false_type { };
	template <> struct is_integral<bool> : public true_type { };
	template <> struct is_integral<char> : public true_type { };
	template <> struct is_integral<signed char> : public true_type { };
	template <> struct is_integral<unsigned char> : public true_type { };
	template <> struct is_integral<wchar_t> : public true_type { };
	template <> struct is_integral<char16_t> : public true_type { };
	template <> struct is_integral<char32_t> : public true_type { };
	template <> struct is_integral<short> : public true_type { };
	template <> struct is_integral<unsigned short> : public true_type { };
	template <> struct is_integral<long> : public true_type { };
	template <> struct is_integral<unsigned long> : public true_type { };
	template <> struct is_integral<long long> : public true_type { };
	template <> struct is_integral<unsigned long long> : public true_type { };
}

#endif