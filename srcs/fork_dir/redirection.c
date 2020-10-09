/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:14:21 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/09 12:14:22 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_fd(t_data *data, int fd)
{
	if (fd == -1)
	{
		errno = 2;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		last_return(data, ft_calloc(2, sizeof(char)));
		return (-1);
	}
	return (1);
}

int		next_cmd(t_cmd *list)
{
	t_cmd *lst;

	if(list->next == NULL)
		return (0);
	lst = list->next;
	if (ft_memcmp(lst->command, ">", 1) == 0
		|| ft_memcmp(lst->command, ">>", 2) == 0)
		return (1);
	return (0);
}

void	redirection_fork(t_cmd *list, char **mem, int *count, t_data *data)
{
	int f;

	*count = 1;

	if (ft_memcmp(list->command, ">>", 2) == 0)
	{
		f = open(list->params[0], O_CREAT | O_APPEND | O_RDWR, 00600);
		if (ft_error_fd(data, f) == -1)
			return ;
		if (next_cmd(list) != 1)
		{
			write(f, *mem, ft_strlen(*mem));
			close(f);
			f = open(list->params[0], O_RDWR);
			free(*mem);
			*mem = prs_mem(f);
		}
		close(f);
	}
	else
	{
		f = open(list->params[0], O_CREAT | O_WRONLY | O_TRUNC, 00600);
		if (ft_error_fd(data, f) == -1)
			return ;
		if (next_cmd(list) != 1)
			write(f, *mem, ft_strlen(*mem));
		close(f);
	}
	data->red = 1;
}
