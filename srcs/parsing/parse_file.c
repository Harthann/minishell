/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:50:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 10:26:11 by nieyraud         ###   ########.fr       */
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

void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("Commands is : [%s]\n", cmd->command);
		for (int i = 0; cmd->params && cmd->params[i]; i++)
			printf("Params[%d] is : [%s]\n", i, cmd->params[i]);
		for(t_cmd *tmp = cmd->redirection; tmp; tmp = tmp->next)
			printf("Redirection of type : [%s] to file [%s]\n", tmp->command, tmp->params[0]);
		cmd = cmd->next;
	}
}