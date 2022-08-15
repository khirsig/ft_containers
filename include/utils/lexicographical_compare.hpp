/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:06:48 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/15 09:40:49 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE
#define LEXICOGRAPHICAL_COMPARE

namespace ft {
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                             InputIterator2 last2) {
    for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}
}  // namespace ft

#endif