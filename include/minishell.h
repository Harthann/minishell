/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacking <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/04/20 16:12:49 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
typedef struct  env_list
{
	char *name;
	char *value;
	struct env_list *next;
}				t_env_lst;

typedef struct	s_data
{
	t_env_lst	*env_var;
	char 		*res_prev_cmd;
}				t_data;

t_env_lst	*ft_envnew(char *name, char *value);
void		ft_addenv(t_env_lst **alst, t_env_lst *new);
void		ft_delenv(t_env_lst **alst, char *name);
void		builtins(char *params);
char		**clean_params(char **params);

#endif
