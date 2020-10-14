/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:00:19 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/14 12:01:35 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		ft_redirect(t_cmd *lst, t_info *p)
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
