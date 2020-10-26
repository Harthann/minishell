/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:34:27 by stbaleba          #+#    #+#             */
/*   Updated: 2020/10/26 14:52:01 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_init(int pnum, t_info *p, t_cmd **mem)
{
	p->end_pass = 0;
	p->pcount = 0;
	p->pnum = pnum;
	p->cmd = mem;
	p->child = 0;
}

int		pnum_l(t_cmd *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (list->command && ft_memcmp(list->command, "|", 2) == 0)
			count++;
		list = list->next;
	}
	return (count * 2);
}

void	pipe_init_close(int **fdpipe, int n, int pnum)
{
	int i;
	int *fd;

	i = 0;
	fd = *fdpipe;
	if (n == 0)
	{
		while (i < pnum)
		{
			pipe(fd + i);
			i += 2;
		}
	}
	else
	{
		while (i < pnum)
			close(fd[i++]);
		free(*fdpipe);
	}
	*fdpipe = fd;
}

void	wait_child(pid_t child, int n)
{
	int		status;
	int		i;

	i = 0;
	waitpid(child, &status, 0);
	if (singleton()->statuspid != -1)
		status = singleton()->statuspid;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
	if (WEXITSTATUS(status) != 0)
		g_last_return = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 0)
		g_last_return = 0;
	else
		g_last_return = 128 + WTERMSIG(status);
	singleton()->statuspid = -1;
}

void	main_fork(t_cmd **list, t_data *data)
{
	int		*fdpipe;
	t_info	p;
	t_cmd	*lst;

	p_init(pnum_l(*list), &p, list);
	lst = *list;
	if (!(fdpipe = (int *)malloc(sizeof(int) * p.pnum)))
		return ;
	pipe_init_close(&fdpipe, 0, p.pnum);
	while (lst)
	{
		if (!p.pcount || (lst->command && !ft_memcmp(lst->command, "|", 2)))
		{
			if (!(g_fg_process = fork()))
				do_builtin(p, fdpipe, lst, data);
			p.pcount += 1;
		}
		lst = lst->next;
	}
	pipe_init_close(&fdpipe, 1, p.pnum);
	wait_child(g_fg_process, p.pcount);
	*list = lst;
}
