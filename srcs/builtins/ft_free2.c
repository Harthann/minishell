/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 08:28:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 10:06:13 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_datas(t_cmd **alst, t_data *data, int *fd)
{
	int		tmp;
	t_cmd	*redirection;

	redirection = (*alst)->redirection;
	tmp = data->exit_code;
	free(data->line);
	free_lst(&(data->env_var));
	free_cmd(&redirection);
	free_cmd(alst);
	free(fd);
	free(data);
	return (tmp);
}
