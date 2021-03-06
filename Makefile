# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 16:28:15 by nieyraud          #+#    #+#              #
#    Updated: 2020/10/27 11:31:36 by nieyraud         ###   ########.fr        #
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

SRC_FILE = 	minishell.c parser.c builtins.c env_funct.c ft_echo.c \
			ft_free.c ft_free2.c pwd_cd.c ft_exec.c cmd_director.c \
			get_next_line.c parse_utils.c fork_utils.c normal_fork.c \
			signal.c  env_funct2.c env_utils.c exit_numeric.c \
			extract.c main_fork.c main_fork2.c move_redir.c \
			parse_file.c sort_redirection.c parse_error.c
			
USELESS = pipe_fork.c reverse_fork.c redirection.c  print_cmd.c fork_parser.c clean_params_utils.c clean_params.c ft_quote.c env_file.c display_built.c error_utils.c

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

sanitize: ${LIBS} ${OBJ} ${INCLUDE} 
	@$(ECHO) "${vertclair}Creating ${NAME}"
	@$(CC) ${FLAGS} ${OPT_FLAGS} ${SAN} -I include -g -L ${LIB} ${OBJ} lib/${LIBFT} -o ${NAME}
	@$(ECHO) "${vertclair}[Minishell ready to use]"

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
