/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:40:36 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/16 08:21:22 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	char	*buffer;
	int		buff;

	if (!(buffer = malloc(2)))
		return (-1);
	buffer[1] = 0;
	while ((buff = read(fd, buffer, 1) > 0) && *buffer != '\n')
	{
		if (*line == NULL)
			*line = ft_strdup(buffer);
		else
			*line = ft_strjoin_free(*line, buffer, 1);
	}
	if (*line == NULL && buff == 1)
		*line = ft_strdup("");
	if (!buff && ft_strlen(buffer))
	{
		buff = ft_strlen(buffer);
		write(1, "\n", 1);
	}
	free(buffer);
	return (buff);
}
