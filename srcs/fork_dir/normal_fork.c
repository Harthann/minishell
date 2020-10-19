/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:13:22 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/15 12:13:51 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_unset_export(t_cmd *lst)
{
	if (lst)
	{
		if (ft_memcmp(lst->command, "export", 7) == 0 && lst->params != NULL)
			return (1);
		else if (ft_memcmp(lst->command, "unset", 5) == 0)
			return (1);
		else if (ft_memcmp(lst->command, "cd", 3) == 0)
			return (1);
	}
	return (0);
}

void		unset_export(t_cmd **list, t_data *data)
{
	t_cmd *lst;

	lst = *list;
	errno = 0;
	if (ft_memcmp(lst->command, "export", 7) == 0 && lst->params != NULL)
	{
		builtins(lst, data);
		lst = lst->next;
	}
	else if (ft_memcmp(lst->command, "unset", 5) == 0)
	{
		builtins(lst, data);
		lst = lst->next;
	}
	else if (ft_memcmp(lst->command, "cd", 3) == 0)
	{
		builtins(lst, data);
		lst = lst->next;
	}
	if (errno != 0)
	{
		g_last_return = errno;
		errno = 0;
	}
	*list = lst;
}
