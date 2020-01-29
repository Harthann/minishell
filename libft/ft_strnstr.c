/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:14:51 by nieyraud          #+#    #+#             */
/*   Updated: 2019/12/17 18:27:47 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*s2)
		return ((char*)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] == s2[j] && (i + j < len))
		{
			j++;
			if (s2[j] == '\0')
			{
				return ((char*)&s1[i]);
			}
		}
		i++;
	}
	return (NULL);
}
