/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:52:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/09 13:23:19 by nieyraud         ###   ########.fr       */
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
			printf("param number : [%d] is : %s\n",i, list->params[i]);
			i++;
		}
		list = list->next;
	}
}
