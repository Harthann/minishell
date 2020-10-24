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
		(name[i] == '\0' && cname[i] == '=') ||
		(cname[i] == '\0' && name[i] == '='))
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

int	check_str(char c1, char c2)
{
	if (c1 == '+' && c2 == '=')
		return (2);
	else if (c1 == '=')
		return (1);
	return (0);
}

void	name_value(char **name, char **value, char *str, int *tab)
{
	char *tname;
	char *tvalue;

	tname = *name;
	tvalue = *value;
//	printf("tab %d\n", tab[1]);
	if(tab[1] == 1)
	{
		tname = ft_substr(str, 0, tab[0] + 1);
		tvalue = ft_strdup(str + tab[0] + 1);
	}
	else if (tab[1] == 2)
	{
		tname = ft_strjoin_free(ft_substr(str, 0, tab[0]), ft_strdup("="), 3);
		tvalue = ft_strdup(str + tab[0] + 2);
	}
	else
	{
		tname = ft_substr(str, 0, tab[0] + 1);
		tvalue = ft_strdup("\0");
	}
	*name = tname;
	*value = tvalue;
}
