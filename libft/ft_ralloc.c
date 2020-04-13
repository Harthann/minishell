/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ralloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:01:51 by marvin            #+#    #+#             */
/*   Updated: 2020/04/13 11:01:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_ralloc(void *ptr, size_t size, size_t new_size)
{
	void	*newptr;

	if (!(newptr = ft_calloc(1, new_size)))
	{
		free(ptr);
		return (NULL);
	}
	if (size <= new_size)
		ft_memcpy(newptr, ptr, size);
	else
		ft_memcpy(newptr, ptr, new_size);
	free(ptr);
	return (ptr);
}