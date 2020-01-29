/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:45:39 by nieyraud          #+#    #+#             */
/*   Updated: 2019/12/16 21:17:48 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int		ft_count_length(unsigned long int n)
{
	int		length;

	length = 1;
	while (n / 16 > 0)
	{
		length++;
		n = n / 16;
	}
	return (length);
}

static	void	ft_fill_number(char *number, unsigned long int n, int nb_length)
{
	char *base;

	base = "0123456789abcdef";
	while (--nb_length >= 0)
	{
		number[nb_length] = base[n % 16];
		n = n / 16;
	}
}

char			*ft_ultox(unsigned long int n)
{
	char	*number;
	int		nb_length;

	nb_length = ft_count_length(n);
	if (!(number = (char*)malloc(sizeof(char) * (nb_length + 1))))
		return (0);
	ft_fill_number(number, n, nb_length);
	number[nb_length] = '\0';
	return (number);
}
