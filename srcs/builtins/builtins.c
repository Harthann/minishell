/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:56:11 by user42            #+#    #+#             */
/*   Updated: 2020/05/16 16:11:22 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_display_export(t_env_lst *lst, char **tab, t_data *data)
{
	
	int i;
	t_env_lst *mem;

	mem = lst;
	i = 0;
	while(tab[i])
	{
		if(ft_memcmp(tab[i], lst->name, ft_strlen(tab[i]) + 1) == 0)
		{
			display("declare -x ", data);
			display(lst->name, data);
			display("=", data);
			display(lst->value, data);
			display("\n", data);
			lst = mem;
			i++;
		}
		else
			lst = lst->next;
	}
}

void	export_display(t_data *data)
{
	char **str;
	int	i;
	int length;
	t_env_lst *mem;

	mem = data->env_var;
	length = lst_size(data);
	str = ft_calloc(length + 1, sizeof(char *));
	i = 0;
	while (mem)
	{
		str[i++] = mem->name;
		mem = mem->next;
	}
	str[i++] = NULL;
	order_tab(&str, length);
//	i = 0;
//	while(str[i])
//	{
//		ft_putstr_fd(str[i], 1);
//		write(1, "\n", 1);
//		i++;
//	}
	ft_display_export(data->env_var, str, data);
}



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
	else if((ft_memcmp(command, "export", 7) == 0 && *params == '\0'))
		export_display(data);
	else if (ft_memcmp(command, "env", 4) == 0)
		env_list(data, params);
	else if (ft_memcmp(command, "export", 7) == 0)
		add_env(params_cl[0], data);
	else if (ft_memcmp(command, "unset", 6) == 0)
		ft_delenv(&(data->env_var), params_cl[0]);
	else if (ft_memcmp(command, "exit", 5) == 0)
		ft_free(data, params_cl);
	else
		ft_exec(command, params, data);
}
