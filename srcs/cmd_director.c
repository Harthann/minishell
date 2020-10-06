/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/06 13:57:47 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_symbol(t_cmd *list)
{
	char *cmd;

	while (list)
	{
		cmd = list->command;
		if ((ft_memcmp(cmd, ">", 1) == 0) ||
			(ft_memcmp(cmd, ">>", 2) == 0) ||
			(ft_memcmp(cmd, "<", 1) == 0) ||
			(ft_memcmp(cmd, "|", 1) == 0))
			return (1);
		list = list->next;
	}
	return (0);
}

int		cmd_director(t_cmd *list, t_data *data)
{
	int count;

	count = 0;
	(void)data;
	while (list)
	{
		if (ft_memcmp(list->command, "exit", 5) == 0)
		{
			builtins(list->command, list->param, data);
			count = 1;
		}
		else if (check_symbol(list) == 0)
			display_parse(list, data, &count);
		else
			fork_parsing(list, data, &count);
		while (count > 0 && list)
		{
			list = list->next;
			count--;
		}
	}
	return (data->status);
}
