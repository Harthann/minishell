/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:23:54 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/22 10:25:06 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;
	int		length;

	length = count * size;
	length ? length : length++;
	if (!(buff = (void*)malloc((length))))
		return (0);
	ft_bzero(buff, length);
	return (buff);
}
