/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:29:36 by user42            #+#    #+#             */
/*   Updated: 2020/05/30 16:29:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_env_lst **alst)
{
	t_env_lst *lst;
	t_env_lst *mem;

	lst = *alst;
	while (lst)
	{
		free(lst->name);
		free(lst->value);
		mem = lst;
		lst = lst->next;
		free(mem);
	}
	free(alst);
}

void	free_builtin(char **params_cl, char **mem)
{
	int i;

	i = 0;
	while (params_cl && params_cl[i] != NULL)
	{
		free(params_cl[i]);
		i++;
	}
	free(params_cl);
	free(mem[0]);
	free(mem);
}

void	free_exec(char *exec, char *path, char **env, char **argv)
{
	int i;

	i = 0;
	free(exec);
	free(path);
	free(env);
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	error_exit(t_data *data)
{
	ft_putstr_fd("Too many arguments\n", 2);
	errno = 7;
	data->last_return = 127;
}

void	ft_free(t_data *data, char **params)
{
	int		i;
	char	*str;

	i = 0;
	errno = 0;
	while (params[i])
		i++;
	if (i > 1)
		error_exit(data);
	else
	{
		str = params[0];
		while (str && *str)
		{
			if (ft_isdigit(*str) == 0)
				errno = 1;
			str++;
		}
		ft_putstr_fd("exit\n", 1);
		if (errno != 0)
			ft_putstr_fd("numeric argument required\n", 2);
		data->status = 0;
		exit(0);
	}
}
