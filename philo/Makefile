# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 18:50:40 by jchakir           #+#    #+#              #
#    Updated: 2022/03/12 13:25:24 by jchakir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

FILES = philo.c atoi.c errors.c philo_utils.c philosopher.c 

OBJ = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) && echo 'All Objects (%.o) cleaned with success'

fclean: clean
	@rm -rf $(NAME) && echo "Programme ($(NAME)) deleted with success"

re: fclean all
