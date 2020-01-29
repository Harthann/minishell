/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:38:10 by nieyraud          #+#    #+#             */
/*   Updated: 2019/10/14 11:48:58 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int a;

	if (n < 0)
	{
		write(fd, "-", 1);
		a = -n;
	}
	else
		a = n;
	if (a > 9)
		ft_putnbr_fd(a / 10, fd);
	ft_putchar_fd(a % 10 + 48, fd);
}
