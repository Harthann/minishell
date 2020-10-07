/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:21:59 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/07 16:51:09 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_param(char *str, int *start)
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
			ret = ft_strjoin_free(ret, extract_dquote(str, start), 1);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, "extract_dollar()", 1);
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
	// printf("BREAKPOINT INSIDE SEPARATOR:\nstr is : [%s]\n", str + *start);
	// read(0, NULL, 1);
	while (is_separator(str, *start + length))
		length++;
	// printf("length is : [%d]\n", length);
	if (!(ret = ft_calloc(sizeof(char), length)))
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

char	*extract_command(char *str, int *start)
{
	char *ret;
	int i;

	i = *start;
	ret = NULL;
	// printf("BREAKPOINT:\nstr is : [%s]\n", str + *start);
	// read(0, NULL, 1);
	if (is_separator(str, *start))
		return(extract_separator(str, start));
	while (str[*start])
	{
		// read(0, NULL, 1);
		if (str[*start] == '\\' && !is_escape(str, *start))
		{
			ret = ft_strapp_free(ret, str[*start + 1]);
			(*start)++;
		}
		else if (str[*start] == '\'' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_quote(str, start), 1);
		else if (str[*start] == '"' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, extract_dquote(str, start), 1);
		else if (str[*start] == '$' && !is_escape(str, *start))
			ret = ft_strjoin_free(ret, "extract_dollar()", 1);
		else if ((str[*start] == ' ' || str[*start] == ';' || is_separator(str, *start)) && !is_escape(str, *start))
			return (ret);
		else
			ret = ft_strapp_free(ret, str[*start]);
		(*start)++;
	}
	// printf("Ret is : [%s]\n", ret);
	// read(0, NULL, 1);
	// printf("Ret value just before return : [%s]\n", ret);
	return (ret);
}