/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/06/24 08:58:24 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_director(t_cmd *list, t_data *data)
{
	int count;

	count = 0;
	while (list)
	{
		if (ft_memcmp(list->command, "exit", 5) == 0)
		{
			builtins(list->command, list->param, data);
			count = 1;
		}
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
