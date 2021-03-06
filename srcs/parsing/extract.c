/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:21:59 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 09:22:36 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_param(char *str, int *start, t_data *data)
{
	char *ret;

	ret = NULL;
	while (str[*start])
	{
		if (str[*start] == '\\' && !is_escape(str, *start))
		{
			ret = ft_strapp_free(ret, str[*start + 1]);
			(*start)++;
		}
		else if (str[*start] == '\'' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_quote(str, start), 3);
		else if (str[*start] == '"' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dquote(str, start, data), 3);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dollar(str, start, data), 3);
		else if (ft_find_char(str[*start], "; |<>") && !is_escape(str, *start))
			return (ret);
		else
			ret = ft_strapp_free(ret, str[*start]);
		(*start)++;
	}
	return (ret);
}

char	*extract_separator(char *str, int *start)
{
	char	*ret;
	int		length;
	int		i;

	length = 0;
	if (str[*start] == ';')
	{
		(*start)++;
		return (NULL);
	}
	while (is_separator(str, *start + length))
		length++;
	if (!(ret = ft_calloc(length + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		ret[i] = str[*start + i];
		i++;
	}
	(*start) += length;
	return (ret);
}

char	*extract_command(char *str, int *start, t_data *data)
{
	char *ret;

	ret = NULL;
	if (is_separator(str, *start))
		return (extract_separator(str, start));
	while (str[*start])
	{
		if (str[*start] == '\\' && !is_escape(str, *start))
		{
			ret = ft_strapp_free(ret, str[*start + 1]);
			(*start)++;
		}
		else if (str[*start] == '\'' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_quote(str, start), 3);
		else if (str[*start] == '"' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dquote(str, start, data), 3);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dollar(str, start, data), 3);
		else if (ft_find_char(str[*start], "; |<>") && !is_escape(str, *start))
			return (ret);
		else
			ret = ft_strapp_free(ret, str[*start]);
		(*start)++;
	}
	return (ret);
}

char	*extract_dollar(char *str, int *start, t_data *data)
{
	t_env_lst	*tmp;
	int			i;
	int			length;
	char		*ret;

	i = *start + 1;
	if (!str[i] || ft_find_char(str[i], "\\;\' \"<>~"))
		return (ft_strdup("$"));
	while (str[i] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		i++;
	tmp = data->env_var;
	length = i - *start - 1;
	while (tmp && ft_strncmp(str + *start + 1, tmp->name, length + 1))
		tmp = tmp->next;
	if (!ft_strncmp(str + *start + 1, "?", 1))
		ret = ft_itoa(g_last_return);
	else if (!tmp)
		ret = ft_strdup("");
	else
		ret = ft_strdup(tmp->value);
	(*start) = i;
	return (ret);
}

char	*last_commands(t_cmd *commands)
{
	while (commands && commands->next)
		commands = commands->next;
	return (commands->command);
}
