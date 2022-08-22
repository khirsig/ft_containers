/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:54:32 by khirsig           #+#    #+#             */
/*   Updated: 2022/08/22 10:13:08 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

#include "../../include/stack.hpp"

typedef NAMESPACE::stack<int>         intstack;
typedef NAMESPACE::stack<std::string> strstack;

void tests();

void debug_padding(std::string title, std::size_t width, char c);

#endif