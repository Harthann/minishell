/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:34:12 by user42            #+#    #+#             */
/*   Updated: 2020/05/30 16:36:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int		check_option(char *command)
{
	while (*command && command)
	{
		if (ft_memcmp(command, "-n", 3) == 0)
			return (0);
		command++;
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

	n = check_option(params_cl[0]);
	i = (n == 0) ? 1 : 0;
	while (params_cl[i])
	{
		display(params_cl[i]);
		if (params_cl[i + 1] != NULL)
			display(" ");
		i++;
	}
	if (n == 1)
		display("\n");
}
