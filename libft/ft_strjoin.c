/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:39:07 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/14 11:49:24 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(str = (char*)malloc(len_s1 + len_s2 + 1)))
		return (0);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + ft_strlen(s1), s2, len_s2 + 1);
	return (str);
}
