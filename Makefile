# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khirsig <khirsig@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 11:34:34 by khirsig           #+#    #+#              #
#    Updated: 2022/08/22 10:14:22 by khirsig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= ft_containers

CC				:= g++
CFLAGS			:= -std=c++98 -Wall -Werror -Wextra

VEC				:= main.cpp									\
				vector/tests.cpp 							\
				vector/utils.cpp 							\

MAP				:= main.cpp									\
				map/tests.cpp 								\
				map/utils.cpp 								\

STACK			:= main.cpp									\
				stack/tests.cpp 							\
				stack/utils.cpp 							\

SET				:= main.cpp									\
				set/tests.cpp 								\
				set/utils.cpp 								\


OS				:= $(shell uname -s)
NUMPROC			:= 8

ifeq ($(OS),Linux)
		NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(OS),Darwin)
		NUMPROC := $(shell sysctl -n hw.ncpu)
endif

SDIR			:= tester
HDIR			:= include
ODIR			:= obj
OBJS			:= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

all: vector map stack set

clean:
	@$(RM) -r $(ODIR)

fclean: clean
	@$(RM) -r *.dSYM $(SDIR)/*.dSYM
	@$(RM) $(NAME) ft_vector std_vector ft_map std_map ft_stack std_stack ft_set std_set

vector:
	@$(CC) $(CFLAGS) -D FT=1 -D VECTOR=1 -o ft_vector $(addprefix $(SDIR)/, $(VEC))
	@$(CC) $(CFLAGS) -D VECTOR=1 -o std_vector $(addprefix $(SDIR)/, $(VEC))

map:
	@$(CC) $(CFLAGS) -D FT=1 -D MAP=1 -o ft_map $(addprefix $(SDIR)/, $(MAP))
	@$(CC) $(CFLAGS) -D MAP=1 -o std_map $(addprefix $(SDIR)/, $(MAP))

stack:
	@$(CC) $(CFLAGS) -D FT=1 -D STACK=1 -o ft_stack $(addprefix $(SDIR)/, $(STACK))
	@$(CC) $(CFLAGS) -D STACK=1 -o std_stack $(addprefix $(SDIR)/, $(STACK))

set:
	@$(CC) $(CFLAGS) -D FT=1 -D SET=1 -o ft_set $(addprefix $(SDIR)/, $(SET))
	@$(CC) $(CFLAGS) -D SET=1 -o std_set $(addprefix $(SDIR)/, $(SET))

