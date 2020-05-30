/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_director.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:51:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/26 10:37:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int     cmd_director(t_cmd *list, t_data *data)
{
	int count;

	count = 0;
    while (list)
	{
		if(ft_memcmp(list->command, "exit", 5) == 0)
		{
	        builtins(list->command, list->param, data);
			count = 1;
		}
		else
        	fork_parsing(list, data, &count);
		while(count > 0 && list)
		{
			list = list->next;
			count--;
		}
    }
    return (data->status);
}
