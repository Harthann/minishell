/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:56:11 by user42            #+#    #+#             */
/*   Updated: 2020/05/14 23:36:22 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *command, char *params, t_data *data)
{
	char **params_cl;

	if (params != NULL)
		params_cl = clean_params(params, data->env_var, data);
	if (ft_memcmp(command, "echo", 5) == 0)
		ft_echo(command, params_cl, data);
	else if (ft_memcmp(command, "pwd", 4) == 0)
		pwd(data, params);
	else if (ft_memcmp(command, "cd", 3) == 0)
		cd(params_cl);
	else if (ft_memcmp(command, "env", 4) == 0 ||
	(ft_memcmp(command, "export", 7) == 0 && *params == '\0'))
		env_list(data);
	else if (ft_memcmp(command, "export", 7) == 0)
		add_env(params_cl[0], data);
	else if (ft_memcmp(command, "unset", 6) == 0)
		ft_delenv(&(data->env_var), params_cl[0]);
	else if (ft_memcmp(command, "exit", 5) == 0)
		ft_free(data, params_cl);
	else
		ft_exec(command, params, data);
}
