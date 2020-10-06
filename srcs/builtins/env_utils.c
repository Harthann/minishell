/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbaleba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:52:17 by stbaleba          #+#    #+#             */
/*   Updated: 2020/10/06 18:28:36 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_char(char *str)
{
	if (*str == '+' || *str == '-' || *str == '['
	|| *str == '{' || *str == '(' || *str == ']'
	|| *str == '}' || *str == ')' || *str == '=')
	{
		ft_putstr_fd("bash: syntax error\n", 10);
		errno = 1;
		return (0);
	}
	str++;
	while(str && *str)
	{
		if (*str == '+' || *str == '-' || *str == '['
		|| *str == '{' || *str == '(' || *str == ']'
		|| *str == '}' || *str == ')')
		{
			ft_putstr_fd("bash: syntax error\n", 10);
			errno = 1;
			return (0);
		}
		str++;
	}
	return (1);
}
