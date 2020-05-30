/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:52:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/20 08:53:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	print_cmd(t_cmd *list)
{
	while (list)
	{
		printf("command : %s\n", list->command);
		printf("param : %s\n", list->param);
		list = list->next;
	}
}
