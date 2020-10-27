/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:34:12 by user42            #+#    #+#             */
/*   Updated: 2020/10/14 15:23:19 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int		check_option(char *cmd)
{
	int i;

	i = 0;
	if (cmd && cmd[i] == '-')
	{
		i++;
		while (cmd && cmd[i])
		{
			if (cmd[i] != 'n')
				return (1);
			i++;
		}
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}

void	display(char *str)
{
	ft_putstr_fd(str, 1);
}

void	ft_echo(char **params_cl)
{
	int n;
	int i;
	int stop;

	stop = 0;
	n = 0;
	if (params_cl)
		n = check_option(params_cl[0]);
	i = (n == 0) ? 1 : 0;
	while (params_cl && params_cl[i])
	{
		if (stop == 1 || check_option(params_cl[i]) == 1)
		{
			stop = 1;
			display(params_cl[i]);
			if (params_cl[i + 1] != NULL)
				display(" ");
		}
		i++;
	}
	if (n == 1 || params_cl == NULL)
		display("\n");
}

int		ft_free2(char **sr, int i)
{
	char *str;

	str = *sr;
	if (str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (str && *str)
	{
		if (ft_isdigit(*str) == 0)
			errno = 1;
		str++;
	}
	*sr = str;
	return (i);
}

char	*get_cwd(int i, char *res)
{
	while (res == NULL)
	{
		i *= 10;
		free(res);
		res = ft_calloc(1000 * i, sizeof(char));
		if (errno != ERANGE && errno != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			free(res);
			return (NULL);
		}
		if (getcwd(res, 1000 * i) == NULL)
		{
			free(res);
			res = NULL;
		}
		else
			res = getcwd(res, 1000 * i);
	}
	return (res);
}
