/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/14 16:01:12 by nieyraud         ###   ########.fr       */
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
	t_cmd *tmp;

	tmp = list;
	while (list)
	{
		if (ft_memcmp(list->command, "exit", 5) == 0)
		{
			builtins(list->command, list->params, data);
			list = list->next;
		}
		if (check_symbol(list) == 0 && check_unset_export(list) == 1)
			unset_export(&list, data);
		else if (list)
			main_fork(&list, data);
	}
	return (data->status);
}
