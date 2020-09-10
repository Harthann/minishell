/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 08:58:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/06/24 09:00:08 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_return(t_data *data, char *m)
{
	if (*m == '\0' && errno == 0)
		data->last_return = 0;
	else if (errno != 0)
		data->last_return = 127;
	else if (errno == 0 && *m != '\0')
	{
		ft_putstr_fd(m, 2);
		data->last_return = 127;
	}
	errno = 0;
	free(m);
}

int		length(char **params)
{
	int count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}
