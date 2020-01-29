/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:30:11 by nieyraud          #+#    #+#             */
/*   Updated: 2019/11/21 08:55:01 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int		nb;
	int		sign;

	nb = 0;
	sign = 1;
	while ((*str == 32 || (*str >= 9 && *str <= 13)) && *str)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str)
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	return (nb * sign);
}
