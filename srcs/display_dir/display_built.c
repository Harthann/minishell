/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 09:11:16 by nieyraud          #+#    #+#             */
/*   Updated: 2020/08/31 09:14:13 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_b(t_cmd *lst, t_data *data)
{
	int		*fde;
	int		status;

	if (!(fde = malloc(sizeof(int) * 2)))
		return ;
	pipe(fde);
	g_fg_process = fork();
	if (g_fg_process == 0)
	{
		close(fde[0]);
		dup2(fde[1], 10);
		builtins(lst->command, lst->param, data);
		exit(0);
	}
	else
	{
		wait(&status);
		errno = WEXITSTATUS(status);
		close(fde[1]);
		unset_export(lst, data);
		if (errno == 2)
			data->last_return = errno;
		else
			last_return(data, prs_mem(fde[0]));
		free(fde);
	}
}

void	display_parse(t_cmd *list, t_data *data, int *count)
{
	while (list)
	{
		errno = 0;
		display_b(list, data);
		list = list->next;
		*count += 1;
	}
}
