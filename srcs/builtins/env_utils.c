/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbaleba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:52:17 by stbaleba          #+#    #+#             */
/*   Updated: 2020/10/14 15:02:21 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(char *name, char *value)
{
	int i;

	i = 0;
	if (ft_find_char(name[i], "+{}-[]()=") == 1)
	{
		ft_putstr_fd("bash: syntax error\n", 2);
		free(name);
		free(value);
		errno = 1;
		return (0);
	}
	i++;
	while (name && name[i])
	{
		if (ft_find_char(name[i], "+{}-[]()") == 1)
		{
			ft_putstr_fd("bash: syntax error\n", 2);
			free(name);
			free(value);
			errno = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_memplus(char *name, char *cname)
{
	int i;

	i = 0;
	while (name[i] && cname[i] && name[i] == cname[i])
		i++;
	if ((name[i] == '\0' && cname[i] == '\0') ||
		(name[i] == '\0' && cname[i] == '='))
		return (0);
	return (1);
}

int	double_tab_length(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
