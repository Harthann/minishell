# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blacking <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/16 10:03:56 by blacking          #+#    #+#              #
#    Updated: 2020/04/20 14:43:55 by blacking         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Werror -Wextra
INC=-Iinclude
NAME=buildtin_test
FILE=builtin_test.c \
	 ./src/builtins/env_funct.c \
	 ./src/builtins/builtins.c \
	 ./src/builtins/clean_params/clean_params.c

OBJ=$(FILE:.c=.o)

all :$(NAME)

$(NAME): $(OBJ) libft.a
	$(CC) $(CFLAGS) $(INC) $(OBJ) lib/libft.a -L./libft -o $(NAME)

libft.a: ./include/libft.h
	make -C libft/

.c.o: $(FILE)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf *.o ./src/*/*.o
	make fclean -C libft/

fclean: clean
	rm -rf $(NAME)

re: fclean all
