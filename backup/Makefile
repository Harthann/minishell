# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blacking <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/16 10:03:56 by blacking          #+#    #+#              #
#    Updated: 2020/04/13 16:00:24 by blacking         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=/usr/bin/clang
CFLAGS=-Wall -Werror -Wextra
HEADERS= libft.h minishell.h
INC_FOLDER=include/
INCLUDE= $(addprefix $(INC_FOLDER), $(HEADERS))
NAME=minishell
FILE=minishell.c
SRC_FOLDER= srcs/
SRCS= $(addprefix $(SRC_FOLDER), $(FILE))
OBJ_FOLDER= object
OBJ= $(addprefix $(OBJ_FOLDER)/, $(FILE:%.c=%.o))

all :$(NAME)

$(NAME): $(OBJ) $(INCLUDE) libft.a
	$(CC) $(CFLAGS) -I$(INC_FOLDER) $(OBJ) lib/libft.a -L./libft -o $(NAME)

libft.a: ./include/libft.h
	/usr/bin/make -C libft/

$(OBJ_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf *.o ./srcs/*.o
	make fclean -C libft/

fclean: clean
	rm -rf $(NAME)

re: fclean all $(HEADERS)
