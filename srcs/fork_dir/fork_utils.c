/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:00:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/06 14:52:57 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_mem2(char **cumul, char *line)
{
	char *mem;

	mem = *cumul;
	*cumul = ft_strjoin(*cumul, line);
	free(mem);
}

char	*prs_mem(int fd)
{
	char	*line;
	char	*cumul;
	int		ret;

	cumul = NULL;
	ret = 1;
	line = NULL;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		prs_mem2(&cumul, line);
		if (ret > 0)
			prs_mem2(&cumul, "\n");
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	return (cumul);
}

int		left_redir(t_cmd *list)
{
	if (!list)
		return (0);
	else if (ft_memcmp(list->command, "<", 1) == 0)
		return (1);
	else
		return (0);
}

int		right_redir(t_cmd *list)
{
	if (!list)
		return (0);
	else if (ft_memcmp(list->command, ">", 1) == 0
			|| ft_memcmp(list->command, ">>", 2) == 0)
		return (1);
	else
		return (0);
}

int		check_pipe(t_cmd *list)
{
	if (!list)
		return (0);
	else if (ft_memcmp(list->command, "|", 1) == 0)
		return (1);
	else
		return (0);
}

int		ft_redirect(t_cmd *lst, p_info *p)
{
	int f;

	f = open(lst->params[0], O_RDONLY);
	p->end_pass += 1;
	while (left_redir(lst->next) == 1)
	{
		close(f);
		lst = lst->next;
		f = open(lst->params[0], O_RDONLY);
		p->end_pass += 1;
	}
	return (f);
}

int		ft_redirect2(t_cmd *lst)
{
	int f;

	if (ft_memcmp(lst->command, ">>", 2) == 0)
		f = open(lst->params[0], O_CREAT | O_APPEND | O_WRONLY, 00600);
	else
		f = open(lst->params[0], O_CREAT | O_WRONLY | O_TRUNC, 00600);
	while (right_redir(lst->next) == 1)
	{
		close(f);
		lst = lst->next;
		if (ft_memcmp(lst->command, ">>", 2) == 0)
			f = open(lst->params[0], O_CREAT | O_APPEND | O_WRONLY, 00600);
		else
			f = open(lst->params[0], O_CREAT | O_WRONLY | O_TRUNC, 00600);
	}
	return (f);
}
