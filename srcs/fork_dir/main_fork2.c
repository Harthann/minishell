/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:53:43 by stbaleba          #+#    #+#             */
/*   Updated: 2020/10/20 10:23:06 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_fd(int *fdpipe, t_info *p, t_cmd *cmd, int j)
{
	int fd;
	int pcount;

	fd = 0;
	pcount = p->pcount;
	if (pcount != 0 && (pcount - 1) * 2 < p->pnum && j == 0)
		fd = fdpipe[(pcount - 1) * 2];
	if (left_redir(cmd) == 1)
		fd = ft_redirect(cmd, p);
	if (fd == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		errno = 1;
	}
	return (fd);
}

int		check_fd2(int *fdpipe, t_info p, t_cmd *cmd)
{
	int fd;
	int pcount;
	int i;

	fd = 1;
	pcount = p.pcount;
	i = 0;
	while (i < p.end_pass)
	{
		cmd = cmd->next;
		i++;
	}
	if ((pcount) * 2 + 1 < p.pnum)
		fd = fdpipe[(pcount) * 2 + 1];
	if (right_redir(cmd) == 1)
		fd = ft_redirect2(cmd);
	return (fd);
}

void	free_cmd(t_cmd **alst)
{
	t_cmd	*lst;
	t_cmd	*mem;
	int		i;

	lst = *alst;
	while (lst)
	{
		i = 0;
		free(lst->command);
		while (lst->params && lst->params[i])
		{
			free(lst->params[i]);
			i++;
		}
		free(lst->params);
		mem = lst;
		lst = lst->next;
		free(mem);
	}
}

void	do_builtin(t_info p, int *fdpipe, t_cmd *lst, t_data *data)
{
	int		fd[2];
	int		i;
	int		j;

	i = 0;
	j = 0;
	errno = 0;
	if (check_pipe(lst) == 1)
		lst = lst->next;
	fd[0] = check_fd(fdpipe, &p, lst->redirection, j);
	if (fd[0] != -1)
	{
		fd[1] = check_fd2(fdpipe, p, lst->redirection);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	}
	while (i < p.pnum)
		close(fdpipe[i++]);
	if (lst->command != NULL && fd[0] != -1)
		builtins(lst, data);
	free_datas(p.cmd, data, fdpipe);
	if (errno != 0)
		exit(errno);
	exit(0);
}
