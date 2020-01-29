/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:37:53 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/14 11:49:32 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if (dstsize == 0)
		return (ft_strlen(src));
	if (ft_strlen(src) == dstsize)
	{
		ft_memcpy(dst, src, dstsize);
		dst[dstsize - 1] = '\0';
	}
	if (ft_strlen(src) < dstsize)
		ft_memcpy(dst, src, ft_strlen(src) + 1);
	if (ft_strlen(src) > dstsize)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (ft_strlen(src));
}
