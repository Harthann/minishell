/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacking <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/04/13 15:53:29 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtin.h"
# include "get_next_line.h"

typedef struct	s_all
{
	int status;
}		t_all;

typedef struct s_quote
{
	int dquote;
	int quote;
}		t_quote;

typedef struct s_cmd
{
	char	*command;
	char	*param;
	char	**split_param;
	void	*next;
}		t_cmd;


int	ft_command_parser(char *str, t_data *data);
void	print_cmd(t_cmd *list);
int		cmd_director(t_cmd *list, t_data *data);

#endif
