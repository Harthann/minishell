/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:09:01 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 10:27:05 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_append(char **t1, int l1, char **t2, int l2)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = ft_calloc(sizeof(char*), l1 + l2 + 1)))
		return (NULL);
	while (t1 && i < l1 && t1[i])
	{
		tab[i] = t1[i];
		i++;
	}
	i = 0;
	while (t2 && i < l2 && t2[i])
	{
		tab[i + l1] = t2[i];
		i++;
	}
	free(t1);
	free(t2);
	return (tab);
}
