/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:41:08 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/07 16:49:59 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*extract_param(char *str, t_quote quote, int *i)
// {
// 	int		length;
// 	char	*param;

// 	length = 0;
// 	quote.escp = 0;
// 	while (str[length] && !is_separator(str[length], &quote))
// 	{
// 		if (str[length] == '\\' && !quote.quote)
// 			!quote.escp ? quote.escp++ : quote.escp--;
// 		else if (str[length] == '\'' && !quote.dquote && !quote.escp)
// 		{
// 			quote.quote++;
// 			quote.quote -= quote.quote == 2 ? 2 : 0;
// 		}
// 		else if (str[length] == '"' && !quote.quote && !quote.escp)
// 		{
// 			quote.dquote++;
// 			quote.dquote -= quote.dquote == 2 ? 2 : 0;
// 		}
// 		else
// 			quote.escp > 0 ? quote.escp-- : 0;
// 		length++;
// 	}
// 	*i += length;
// 	return (param = ft_substr(str, 0, length));
// }

int 	is_escape(char *str, int i)
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



char **param_cpy(char **dest, char** src)
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

char **parse_param(char *str, int *i)
{
	char	**params_list;
	char	**tmp;
	char	*param;
	int		nb;

	params_list = NULL;
	nb = 0;
	printf("Entered parse param\n");
	while ((param = extract_param(str, i)))
	{
		while (str[*i] && str[*i] == ' ')
			(*i)++;
		nb++;
		tmp = params_list;
		if (!(params_list = ft_calloc(nb + 1, sizeof(char *))))
			return (NULL);
		params_list = param_cpy(params_list, tmp);
		params_list[nb - 1] = param;
	}
	printf("Finished creating params list\n");
	return (params_list);
}

t_cmd	*new_command(char *str, int *start)
{
	t_cmd	*cmd;

	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	// printf("BREAKPOINT INSIDE NEW COMMAND:\nstr is : [%s]\n", str + *start);
	// read(0, NULL, 1);
	while (str[*start] == ' ' && str[*start] != '\0')
		(*start)++;
	// printf("Parse command\n");
	cmd->command = extract_command(str, start);
	(*start)++;
	// printf("Parse param, command was : [%s] [%s]\n\n\n\n", cmd->command, str + *start);
	cmd->params = parse_param(str, start);
	// printf("Parse param, sttr left is : [%s]\n\n\n\n", str + *start);
	return (cmd);
}

int		ft_command_parser(char *str, t_data *data)
{
	t_cmd	*commands;
	int		i;

	i = 0;
	commands = NULL;
	printf("Command parser\n");
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		add_back(&commands, new_command(str, &i));
		while ((str[i] == ';' || str[i] == ' ') && str[i])
			i++;
		// printf("Finished creating one command, left str : [%s]\n\n\n\n", str + i);
	}
	(void)data;
	print_cmd(commands);
	// cmd_director(commands, data);
	free_command(&commands);
	return (1);
}
