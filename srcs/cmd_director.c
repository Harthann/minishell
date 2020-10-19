/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/19 14:54:36 by nieyraud         ###   ########.fr       */
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

int		check_first_cmd(t_cmd **list)
{
	t_cmd *lst;

	lst = *list;
	if (lst && (ft_memcmp(lst->command, ";", 2) == 0 ||
		ft_memcmp(lst->command, "|", 2) == 0))
	{
		if (ft_memcmp(lst->command, ";", 2) == 0)
			ft_putstr_fd(SYNERROR, 2);
		else if (ft_memcmp(lst->command, "|", 2) == 0)
			ft_putstr_fd(SYNERRORP, 2);
		g_last_return = 2;
		return (0);
	}
	return (1);
}

int		cmd_director(t_cmd *list, t_data *data)
{
	t_cmd *tmp;

	tmp = list;
	if (check_first_cmd(&tmp) == 0)
		return (data->status);
	while (list)
	{
		if (ft_memcmp(list->command, "exit", 5) == 0)
		{
			builtins(list, data);
			list = list->next;
		}
		if (check_symbol(list) == 0 && check_unset_export(list) == 1)
			unset_export(&list, data);
		else if (list)
			main_fork(&list, data);
	}
	return (data->status);
}
