/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbaleba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:34:27 by stbaleba          #+#    #+#             */
/*   Updated: 2020/10/14 15:53:31 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_init(int pnum, t_info *p)
{
	p->end_pass = 0;
	p->pcount = 0;
	p->pnum = pnum;
}

int		pnum_l(t_cmd *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (ft_memcmp(list->command, "|", 2) == 0)
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
	}
	*fdpipe = fd;
}

void	wait_child(t_data *data)
{
	int status;

	while ((wait(&status)) > 0)
		;
	if (status != 0)
		data->last_return = 127;
	else
		data->last_return = 0;
}

void	main_fork(t_cmd **list, t_data *data)
{
	int		*fdpipe;
	t_info	p;
	t_cmd	*lst;

	p_init(pnum_l(*list), &p);
	lst = *list;
	if (!(fdpipe = (int *)malloc(sizeof(int) * p.pnum)))
		return ;
	pipe_init_close(&fdpipe, 0, p.pnum);
	while (lst)
	{
		if (p.pcount == 0 || ft_memcmp(lst->command, "|", 2) == 0 ||
		ft_memcmp(lst->command, ";", 2) == 0)
		{
			if (fork() == 0)
				do_builtin(p, fdpipe, lst, data);
			p.pcount += 1;
		}
		lst = lst->next;
	}
	pipe_init_close(&fdpipe, 1, p.pnum);
	free(fdpipe);
	wait_child(data);
	*list = lst;
}
