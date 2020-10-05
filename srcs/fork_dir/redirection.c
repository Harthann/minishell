/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 08:19:05 by user42            #+#    #+#             */
/*   Updated: 2020/10/05 15:38:26 by nieyraud         ###   ########.fr       */
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

int		file_opener(t_cmd **list)
{
	int fd;

	fd = -1;
	while (!ft_memcmp((*list)->command, ">>", 2)
		|| !ft_memcmp((*list)->command, ">", 1))
	{
		if (fd != -1)
			close(fd);
		if (ft_memcmp((*list)->command, ">>", 2) == 0)
			fd = open((*list)->param, O_CREAT | O_APPEND | O_RDWR, 00600);
		else
			fd = open((*list)->param, O_CREAT | O_WRONLY | O_TRUNC, 00600);
		if (!(*list)->next || (ft_memcmp((*list)->next->command, ">>", 2)
			&& ft_memcmp((*list)->next->command, ">", 1)))
			return (fd);
		*list = (*list)->next;
	}
	return (fd);
}

void	redirection_fork(t_cmd *list, char **mem, int *count, t_data *data)
{
	int f;

	*count = 1;
	f = file_opener(&list);
	if (ft_memcmp(list->command, ">>", 2) == 0)
	{
		if (ft_error_fd(data, f) == -1)
			return ;
		write(f, *mem, ft_strlen(*mem));
		close(f);
		f = open(list->param, O_RDWR);
		free(*mem);
		*mem = prs_mem(f);
	}
	else
	{
		if (ft_error_fd(data, f) == -1)
			return ;
		write(f, *mem, ft_strlen(*mem));
		close(f);
	}
	data->red = 1;
}
