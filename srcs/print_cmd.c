/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:52:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/16 09:06:13 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	print_cmd(t_cmd *list)
{
	int i;

	while (list)
	{
		i = 0;
		printf("command : %s\n", list->command);
		while (list->params && list->params[i])
		{
			printf("param number : [%d] is : %s\n", i, list->params[i]);
			i++;
		}
		list = list->next;
	}
}

void	print_addr(t_cmd *list, t_data *data)
{
	int i;
	t_env_lst *tmp;

	while (list)
	{
		i = 0;
		printf("command : %p\n", list->command);
		while (list->params && list->params[i])
		{
			printf("param number : [%d] is : %p\n", i, list->params[i]);
			i++;
		}
		list = list->next;
	}
	printf("Printing env addresses\n");
	tmp = data->env_var;
	while (tmp)
	{
		printf ("Name : [%p]\n", tmp->name);
		printf ("Value` : [%p]\n", tmp->value);
		tmp = tmp->next;
	}
}
