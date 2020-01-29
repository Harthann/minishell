/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:55:41 by nieyraud          #+#    #+#             */
/*   Updated: 2019/12/16 20:55:14 by nieyraud         ###   ########.fr       */
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
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(str = (char*)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	ft_memcpy(str, s1, len_s1 + 1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	state == 1 || state == 3 ? free(s1) : 0;
	state == 2 || state == 3 ? free(s2) : 0;
	return (str);
}
