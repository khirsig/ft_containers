/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:05:10 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 10:19:17 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP_
#define TESTER_HPP_

#include <iostream>

#ifdef VECTOR
#include "vector/utils.hpp"
#endif

#ifdef MAP
#include "map/utils.hpp"
#endif

#ifdef SET
#include "set/utils.hpp"
#endif

#ifdef STACK
#include "stack/utils.hpp"
#endif

#endif