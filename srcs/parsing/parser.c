/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:41:08 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/25 11:28:46 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escape(char *str, int i)
{
	if (i == 0)
		return (0);
	if (str[i - 1] == '\\')
	{
		if (is_escape(str, i - 1))
			return (0);
		else
			return (1);
	}
	return (0);
}

char	**param_cpy(char **dest, char **src)
{
	int i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	**parse_param(char *str, int *i, t_data *data)
{
	char	**params_list;
	char	**tmp;
	char	*param;
	int		nb;

	params_list = NULL;
	nb = 0;
	while ((param = extract_param(str, i, data)))
	{
		while (str[*i] && str[*i] == ' ')
			(*i)++;
		nb++;
		tmp = params_list;
		if (!(params_list = ft_calloc(nb + 1, sizeof(char *))))
			return (NULL);
		params_list = param_cpy(params_list, tmp);
		free(tmp);
		params_list[nb - 1] = param;
	}
	return (params_list);
}

t_cmd	*new_command(char *str, int *start, t_data *data)
{
	t_cmd	*cmd;

	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	while (str[*start] == ' ' && str[*start] != '\0')
		(*start)++;
	cmd->command = extract_command(str, start, data);
	if (!cmd->command)
	{
		free(cmd);
		return (NULL);
	}
	while (str[*start] == ' ' && str[*start])
		(*start)++;
	if (!ft_strncmp(cmd->command, "|", 1))
		return (cmd);
	if (!ft_strncmp(cmd->command, "<", 1) || !ft_strncmp(cmd->command, ">", 1))
		cmd->params = parse_file(str, start, data);
	else
		cmd->params = parse_param(str, start, data);
	return (cmd);
}

int		ft_command_parser(char *str, t_data *data)
{
	t_cmd	*commands;
	int		i;

	i = 0;
	commands = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (create_commands(&commands, str, data, &i))
			break ;
		while (str[i] == ' ' && str[i])
			i++;
	}
	data->status++;
	sort_redirection(commands);
	if (commands)
		cmd_director(commands, data);
	free_command(&commands);
	return (i);
}
