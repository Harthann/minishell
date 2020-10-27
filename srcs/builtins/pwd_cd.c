/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:36:30 by user42            #+#    #+#             */
/*   Updated: 2020/10/14 17:24:28 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		length(char **params)
{
	int count;

	count = 0;
	while (params && params[count])
		count++;
	return (count);
}

void	pwd(void)
{
	char	*res;
	t_data	*data;

	data = singleton();
	if (data->path)
	{
		ft_putstr_fd(data->path, 1);
		write(1, "\n", 2);
	}
	else
	{
		res = get_cwd(1, NULL);
		if (res != NULL)
		{
			ft_putstr_fd(res, 1);
			write(1, "\n", 2);
			free(res);
		}
	}
}

char	*home_dir(t_env_lst *lst)
{
	while (lst)
	{
		if (ft_memplus("HOME", lst->name) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	cd(char **params_cl, t_data *data)
{
	int n;

	n = length(params_cl);
	if (n == 0 || ft_memcmp(params_cl[0], "~", 2) == 0)
		chdir(home_dir(data->env_var));
	else if (n == 1)
	{
		chdir(params_cl[0]);
		if (errno != 0 && g_fg_process != 0)
		{
			error_cd(params_cl[0]);
			return ;
		}
	}
	else
	{
		errno = 1;
		ft_putstr_fd(strerror(7), 2);
		write(2, "\n", 2);
		return ;
	}
	free(data->path);
	data->path = get_cwd(1, NULL);
}
