/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:03:44 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/19 20:56:28 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!(str = ft_calloc(sizeof(char), (len + 2))))
		return (0);
	if (start > ft_strlen(s))
		return (str);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
