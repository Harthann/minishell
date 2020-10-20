/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:50:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 11:28:38 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_file(char *str, int *i, t_data *data)
{
	char	**params_list;
	int		nb;

	params_list = NULL;
	nb = 0;
	if (!(params_list = ft_calloc(2, sizeof(char *))))
		return (NULL);
	params_list[0] = extract_param(str, i, data);
	while (str[*i] == ' ')
		(*i)++;
	return (params_list);
}
