/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/22 14:29:40 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_symbol(t_cmd *list)
{
	char *cmd;

	while (list && list->command)
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

int		check_lst_exit(t_cmd *list)
{
	t_info	p;
	t_cmd	*cmd;
	int		i;

	i = 0;
	p_init(pnum_l(list), &p, &list);
	if (list->command && ft_memcmp(list->command, "exit", 5) == 0)
	{
		i = 1;
		cmd = list->redirection;
		if (!redirect_exit(p, cmd))
			return (0);
		list = list->next;
	}
	if (i == 0)
		return (0);
	if (list == NULL ||
	(list->command && ft_memcmp(list->command, "|", 2) != 0))
		return (1);
	return (0);
}

int		cmd_director(t_cmd *list, t_data *data)
{
	t_cmd *tmp;

	tmp = list;
	while (list)
	{
		if (check_lst_exit(list) != 0)
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
