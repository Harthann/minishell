/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:49:21 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/20 14:28:03 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_length(unsigned int n)
{
	int		length;

	length = 1;
	while (n / 10 > 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

static	void	ft_fill_number(char *number, int n, int nb_length)
{
	unsigned int num;

	if (n < 0)
	{
		number[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (--nb_length >= 0)
	{
		if (number[nb_length] != '-')
		{
			number[nb_length] = num % 10 + '0';
			num = num / 10;
		}
	}
}

char			*ft_itoa(int n)
{
	char	*number;
	int		nb_length;

	if (n < 0)
		nb_length = 1 + ft_count_length(-n);
	else
		nb_length = ft_count_length(n);
	if (!(number = ft_calloc(sizeof(char), (nb_length + 1))))
		return (0);
	ft_fill_number(number, n, nb_length);
	return (number);
}
