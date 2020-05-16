# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 16:28:15 by nieyraud          #+#    #+#              #
#    Updated: 2020/05/16 15:06:27 by blacking         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################
#		COLOR		#
#####################

rose=\033[1;31m
violetfonce=\033[0;35m
violetclair=\033[1;35m
neutre=\033[0m
cyanfonce=\033[0;36m
cyanclair=\033[1;36m
vertfonce=\033[0;32m
vertclair=\033[1;32m
rouge=\033[31m

#####################
#		SOURCES		#
#####################
NAME = minishell

SRC_FILE = 	minishell.c parser.c print_cmd.c \
			builtins.c env_funct.c ft_echo.c \
			ft_free.c pwd_cd.c ft_exec.c \
			cmd_director.c clean_params.c \
			env_file.c ft_quote.c get_next_line.c \
			init_env.c parse_utils.c \
			fork_parser.c fork_utils.c normal_fork.c \
			reverse_fork.c redirection.c pipe_fork.c \
			signal.c error_utils.c env_funct2.c

#############################
#		DIRCTORIES PATH		#
#############################

PATH = ${shell find srcs -type d}
OBJ_PATH = objs
vpath %.c $(foreach dir, $(PATH), $(dir))

#################################
#		FILES	VARIABLE		#
#################################

SRC		= ${SRC_FILE}
SRCS	= $(addprefix ${PATH}, ${SRC_FILE})
OBJ		= ${addprefix ${OBJ_PATH}/, ${SRC_FILE:%.c=%.o}}
INCLUDE	= include/libft.h

#########################
#			FLAGS		#
#########################

FLAGS = -Wall -Werror -Wextra -O2 -march=native
SAN = -g3 -fsanitize=address
OPT_FLAGS = -flto

#########################
#		LIBRARIES		#
#########################

LIBFT	= libft.a
LIB = lib/
LIBS = ${addprefix $(LIB), ${LIBFT}}

########################
#		COMMAND			#
#######################

CC= /usr/bin/clang
MKDIR= /bin/mkdir
ECHO=echo
RM=/bin/rm

#############################
#			RULES			#
#############################

all : $(NAME)

$(NAME) : ${LIBS} ${OBJ} ${INCLUDE} 
	@$(ECHO) "${vertclair}Creating ${NAME}"
	@$(CC) ${FLAGS} ${OPT_FLAGS} -I include -g -L ${LIB} ${OBJ} lib/${LIBFT} -o ${NAME}
	@$(ECHO) "${vertclair}[Minishell ready to use]"

${LIBS} : ./include/libft.h
	/usr/bin/make -C libft/

${OBJ_PATH}/%.o: %.c ${INCLUDE}
	@$(MKDIR) -p ${OBJ_PATH}
	@$(ECHO) "${cyanfonce}Compiling ${notdir $(basename $@)}"
	@$(CC) $(FLAGS) -c -o $@ -I include/ $<

clean :
	@$(ECHO) "${rouge}Removing objects files"
	@$(RM) -rf ${OBJ_PATH}
	@/usr/bin/make clean -C libft

run : all
	@$(ECHO) $(neutre)
	@./${NAME}

fclean : clean
	@$(ECHO) "${rose}Removing ${NAME}"
	@$(RM) -f $(NAME) ${LIBS}

re : fclean all

.PHONY : all clean fclean re
