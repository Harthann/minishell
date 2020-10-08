/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:11:48 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/06 14:04:35 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_function2(int f, int *fd, char **mem)
{
	close(fd[0]);
	free(*mem);
	*mem = prs_mem(f);
	dup2(fd[1], 1);
	ft_putstr_fd(*mem, 1);
	exit(0);
}

void	parent_function2(int *fds, int *fdb, char **mem, t_data *data)
{
	wait(NULL);
	close(fdb[1]);
	close(fds[1]);
	free(*mem);
	*mem = prs_mem(fds[0]);
	last_return(data, prs_mem(fdb[0]));
	free(fds);
	free(fdb);
}

void	reverse_red_fork2(t_cmd *list, t_data *data, char **mem, int fd)
{
	int		*fds;
	int		*fdb;
	pid_t	p;

	if (!(fds = malloc(sizeof(int) * 2)))
		fds = 0;
	if (!(fdb = malloc(sizeof(int) * 2)))
		fdb = 0;
	pipe(fds);
	pipe(fdb);
	p = fork();
	if (p == 0)
	{
		close(fdb[0]);
		close(fds[0]);
		dup2(fds[1], 1);
		dup2(fd, 0);
		dup2(fdb[1], 10);
		builtins(list->command, list->param, data);
		exit(0);
	}
	else
		parent_function2(fds, fdb, mem, data);
}

void	reverse_red_fork(t_cmd *list, t_data *data, char **mem, int *count)
{
	t_cmd	*m;
	pid_t	p;
	int		*fd;
	int		f;

	*count = 2;
	m = list->next;
	while((left_redir(m->next) == 1))
	{
		m = m->next;
		*count += 1;
	}
	f = open(m->param, O_RDWR);
	if (ft_error_fd(data, f) == -1)
		return ;
	if (!(fd = malloc(sizeof(int) * 2)))
		return ;
	pipe(fd);
	p = fork();
	if (p == 0)
		child_function2(f, fd, mem);
	else
	{
		wait(NULL);
		close(fd[1]);
		close(f);
		reverse_red_fork2(list, data, mem, fd[0]);
		free(fd);
	}
}
