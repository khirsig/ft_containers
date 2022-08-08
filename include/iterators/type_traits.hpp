/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:22:08 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/08 09:03:02 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS

namespace ft {

/*
It was not possible to use my own iterator tags, as they would only work
with the ft::iterators and not with the std::iterators.

struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bitdirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bitdirectional_iterator_tag { };
*/

typedef std::output_iterator_tag output_iterator_tag;
typedef std::input_iterator_tag input_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

template <class Iterator>
class iterator_traits {
   public:
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*> {
   public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
   public:
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class Iterator>
typename ft::iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&) {
    return (typename ft::iterator_traits<Iterator>::iterator_category());
}
}  // namespace ft

#endif