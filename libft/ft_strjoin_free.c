/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:55:41 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/08 15:09:55 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, char state)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(str = ft_calloc(len_s1 + len_s2 + 2, sizeof(char))))
		return (NULL);
	ft_memcpy(str, s1, len_s1 + 1);
	ft_memcpy(str + len_s1, s2, len_s2);
	state == 1 || state == 3 ? free(s1) : 0;
	state == 2 || state == 3 ? free(s2) : 0;
	return (str);
}
