/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:40:10 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/26 13:34:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "libft.h"

# define BUFFER_SIZE 4096

typedef struct		s_stock
{
	char			*str;
	int				fd;
	struct s_stock	*next;
}					t_stock;

int					get_next_line(int fd, char **line);

#endif
