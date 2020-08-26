/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:36:30 by user42            #+#    #+#             */
/*   Updated: 2020/06/26 09:06:36 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *params)
{
	char *res;

	if (*params == '\0')
	{
		errno = 0;
		res = ft_calloc(1000, sizeof(char));
		res = getcwd(res, 1000);
		ft_putstr_fd(res, 1);
		write(1, "\n", 2);
		free(res);
	}
	else
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 10);
		write(10, "\n", 2);
	}
}

void	cd(char **params_cl)
{
	int n;

	n = length(params_cl);
	if (n == 1)
	{
		errno = 0;
		chdir(params_cl[0]);
		if (errno != 0 && g_fg_process != 0)
		{
			write(2, "Minishell: cd: ", 16);
			ft_putstr_fd(params_cl[0], 2);
			write(2, ": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 2);
		}
	}
	else if(g_fg_process != 0)
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
	}
}
