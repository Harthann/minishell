/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:49:45 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/18 14:46:38 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_words(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static	int		ft_count_letters(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		nb_words;
	int		i;

	nb_words = ft_count_words(s, c);
	if (!(split_strs = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		return (0);
	i = 0;
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		if (!(split_strs[i] = ft_substr(s, 0, ft_count_letters(s, c))))
		{
			while (i >= 0)
				free(split_strs[i--]);
			free(split_strs);
			return (0);
		}
		while (*s != c && *s)
			s++;
		i++;
	}
	split_strs[i] = NULL;
	return (split_strs);
}
