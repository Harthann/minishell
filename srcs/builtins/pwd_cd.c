/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:36:30 by user42            #+#    #+#             */
/*   Updated: 2020/05/30 16:37:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *params)
{
	char *res;

	if (*params == '\0')
	{
		res = ft_calloc(1000, sizeof(char));
		res = getcwd(res, 1000);
		ft_putstr_fd(res, 1);
		write(1, "\n", 2);
		free(res);
	}
	else
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
	}
}

void	cd(char **params_cl)
{
	int n;

	n = length(params_cl);
	if (n == 1)
	{
		chdir(params_cl[0]);
		if (errno != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 2);
		}
	}
	else
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
	}
}
