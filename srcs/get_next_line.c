/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:40:36 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/26 17:55:07 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		reading_file(int fd, char **stock)
{
	char	*buffer;
	int		buff;

	buff = 1;
	if (ft_search(*stock, '\n') != -1)
		return (1);
	if (!(buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	*buffer = '\0';
	while (ft_search(buffer, '\n') == -1 && buff > 0)
	{
		buff = read(fd, buffer, BUFFER_SIZE);
		if (buff >= 0)
		{
			buffer[buff] = '\0';
			if (!(*stock))
				*stock = ft_substr(buffer, 0, buff);
			else
				*stock = ft_strjoin_free(*stock, buffer, 1);
		}
	}
	free(buffer);
	return (buff > 0 ? 1 : buff);
}

int		stock_line(int fd, char **line, char **stock)
{
	char	*to_free;
	int		length;
	int		error;

	if (!line)
		return (-1);
	if ((error = reading_file(fd, stock)) < 0)
		return (-1);
	length = ft_search(*stock, '\n');
	length == -1 ? length = ft_strlen(*stock) : length;
	if (!(*line = ft_substr(*stock, 0, length)))
		return (-1);
	to_free = *stock;
	*stock = ft_substr(*stock, length + 1, ft_strlen((*stock) + length + 1));
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
	return (error);
}

int		get_next_line(int fd, char **line)
{
	static	char	*stock;
	int				error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	error = stock_line(fd, line, &stock);
	if (stock && (error == -1 || error == 0))
	{
		free(stock);
		stock = NULL;
	}
	return (error);
}
