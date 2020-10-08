/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:21:59 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/08 16:21:19 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_param(char *str, int *start, t_env_lst *env)
{
	char *ret;
	int i;

	i = *start;
	ret = NULL;
	
	while (str[*start])
	{
		if (str[*start] == '\\' && !is_escape(str, *start))
		{
			ret = ft_strapp_free(ret, str[*start + 1]);
			(*start)++;
		}
		else if (str[*start] == '\'' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_quote(str, start), 1);
		else if (str[*start] == '"' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dquote(str, start, env), 1);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dollar(str, start, env), 2);
		else if ((str[*start] == ' ' || str[*start] == ';' || is_separator(str, *start)) && !is_escape(str, *start))
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

char	*extract_command(char *str, int *start, t_env_lst *env)
{
	char *ret;
	int i;

	i = *start;
	ret = NULL;
	if (is_separator(str, *start))
		return(extract_separator(str, start));
	while (str[*start])
	{
		if (str[*start] == '\\' && !is_escape(str, *start))
		{
			ret = ft_strapp_free(ret, str[*start + 1]);
			(*start)++;
		}
		else if (str[*start] == '\'' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_quote(str, start), 1);
		else if (str[*start] == '"' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dquote(str, start, env), 1);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dollar(str, start, env), 2);
		else if ((str[*start] == ' ' || str[*start] == ';'
				|| is_separator(str, *start)) && !is_escape(str, *start))
			return (ret);
		else
			ret = ft_strapp_free(ret, str[*start]);
		(*start)++;
	}
	return (ret);
}

char	*extract_dollar(char *str, int *start, t_env_lst *env)
{
	t_env_lst *tmp;
	int i;

	i = *start + 1;
	if (str[i] == ' ' || str[i] == '\'' || is_separator(str, i))
		return (ft_strdup("$"));
	while (str[i] && str[i + 1] != ' ' && str[i + 1] != '\'' && str[i + 1] != '$'
			&& str[i + 1] !=  '"' && !is_separator(str, i + 1))
		i++;
	tmp = env;
	while (tmp && ft_strncmp(str + *start + 1, tmp->name, i - *start - 1))
		tmp = tmp->next;
	(*start) = i;
	if (!tmp)
		return (ft_strdup(""));
	else
		return (ft_strdup(tmp->value));
}