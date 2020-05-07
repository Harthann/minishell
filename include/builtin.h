/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacking <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/04/26 15:52:31 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H

# define BUILTIN_H

# include "libft.h"
# include <stdio.h>
# include <sys/types.h>

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
	int			last_return;
	int			status;
}				t_data;

// t_env_lst	*ft_envnew(char *name, char *value);
// void		ft_addenv(t_env_lst **alst, t_env_lst *new);
// void		ft_delenv(t_env_lst **alst, char *name);
// void		builtins(char *command, char *params, t_data *data);
// char		**clean_params(char *params, t_env_lst *lst, t_data *data);
// char		*env_value(char *str, int index, t_env_lst *lst);
// char		*env_value2(char *str, t_env_lst *lst);
// char		*ft_quote(char *params, int index, t_env_lst *lst);
// void		ft_echo(char *command, char **params_cl, t_data *data);
// void		ft_putstr(char *str);
// void		pwd(t_data *data);
// void		cd(char **params_cl);
// void		env_list(t_data *data);
// void		display(char *str, t_data *data);
// void		add_env(char *str, t_data *data);
// void		ft_free(t_data *data, char **params_cl);
// void		ft_exec(char *exec, t_data *data);

#endif