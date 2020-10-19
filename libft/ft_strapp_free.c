/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:11:46 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/19 11:26:40 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strapp_free(char *str, char c)
{
	char	*ret;
	int		i;
	int		length;

	i = 0;
	if (!str)
		length = 1;
	else
		length = ft_strlen(str) + 1;
	if (!(ret = ft_calloc(sizeof(char), (length + 1))))
		return (NULL);
	while (str && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	free(str);
	ret[i] = c;
	return (ret);
}
