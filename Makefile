# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 11:34:34 by khirsig           #+#    #+#              #
#    Updated: 2022/08/19 13:42:58 by khirsig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= ft_containers

CC				:= g++
CFLAGS			:= -std=c++98 -Wall -Werror -Wextra -g -fsanitize=address

VEC				:= main.cpp									\
				vector/tests.cpp 							\
				vector/utils.cpp 							\

MAP				:= main.cpp									\
				map/tests.cpp 								\
				map/utils.cpp 								\

OS				:= $(shell uname -s)
NUMPROC			:= 8

ifeq ($(OS),Linux)
		NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(OS),Darwin)
		NUMPROC := $(shell sysctl -n hw.ncpu)
endif

SDIR			:= src
HDIR			:= include
ODIR			:= obj
OBJS			:= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

all: vector map

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r *.dSYM $(SDIR)/*.dSYM
	$(RM) $(NAME) ft_vector std_vector ft_map std_map

vector:
	@$(CC) $(CFLAGS) -D TEST=1 -D VECTOR=1 -o ft_vector $(addprefix $(SDIR)/, $(VEC))
	@$(CC) $(CFLAGS) -D VECTOR=1 -o std_vector $(addprefix $(SDIR)/, $(VEC))

map:
	@$(CC) $(CFLAGS) -D TEST=1 -D MAP=1 -o ft_map $(addprefix $(SDIR)/, $(MAP))
	@$(CC) $(CFLAGS) -D MAP=1 -o std_map $(addprefix $(SDIR)/, $(MAP))

