/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:13:22 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/09 13:57:41 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset_export(t_cmd *list, t_data *data)
{
	if (ft_memcmp(list->command, "export", 7) == 0 && list->params != NULL)
	{
		builtins(list->command, list->params, data);
		return (1);
	}
	else if (ft_memcmp(list->command, "unset", 5) == 0)
	{
		builtins(list->command, list->params, data);
		return (1);
	}
	else if (ft_memcmp(list->command, "cd", 3) == 0)
	{
		builtins(list->command, list->params, data);
		return (1);
	}
	return (0);
}

void	child_function(int *fd, int *fde, t_cmd *lst, t_data *data)
{
	close(fde[0]);
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(fde[1], 10);
	builtins(lst->command, lst->params, data);
	exit(0);
}

void	normal_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int		*fd;
	int		*fde;
	int		status;

	*count = 1;
	if (!(fd = malloc(sizeof(int) * 2)))
		return ;
	if (!(fde = malloc(sizeof(int) * 2)))
		return ;
	pipe(fd);
	pipe(fde);
	g_fg_process = fork();
	if (g_fg_process == 0)
		child_function(fd, fde, lst, data);
	else
	{
		wait(&status);
		close(fde[1]);
		close(fd[1]);
		free(*mem);
		*mem = prs_mem(fd[0]);
		free(fd);
		unset_export(lst, data);
		if ((WEXITSTATUS(status)) == 2 || WEXITSTATUS(status) == 1)
			data->last_return = 127;
		else
			last_return(data, prs_mem(fde[0]));
//		last_return(data, prs_mem(fde[0]));
		free(fde);
	}
}
