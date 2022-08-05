# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 11:34:34 by khirsig           #+#    #+#              #
#    Updated: 2022/08/05 13:47:55 by khirsig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= ft_containers

CC				:= g++
CFLAGS			:= -std=c++98 -Wall -Werror -Wextra -style=Google

SRCS			:= main.cpp									\

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

all:
	@make $(NAME) -j$(NUMPROC)

$(NAME): $(ODIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1;32m$(NAME) compiled and linked.\033[0m"

$(ODIR)/%.o: $(SDIR)/%.cpp $(HDIR)/*.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r *.dSYM $(SDIR)/*.dSYM
	$(RM) $(NAME)
	$(RM) ft_test
	$(RM) std_test

test:$(ODIR) $(OBJS)
	@$(CC) $(CFLAGS) -D TEST=1 -o ft_test $(SDIR)/$(SRCS)
	@make clean
	@$(CC) $(CFLAGS) -o std_test $(SDIR)/$(SRCS)
re: fclean all
