#include "minishell.h"

int		c_p(char *params)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while(params && params[i])
	{
		if(params[i] == ' ' || params[i] == '|')
			n++;
		i++;
	}
	return (n + 1);
}

char *ft_exception(char *s, t_env_lst *lst, t_data *data, int *index)
{
	char *res;

	if(s[*index] == 39 || s[*index] == 34)
	{
		res = quote_check(s, lst, *index);
		*index += count_quotechar(s, *index);
		return (res);
	}
	else
	{
		res = dollar_check(data, s, lst, *index);
		if (s[*index + 1] == '?')
			*index += 1;
		else
			*index += count_char(s + *index + 1);
		return (res);
	}
}

char *ft_str(char *s, int count, t_env_lst *lst, t_data *data)
{
	char *str;
	char *res;
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(str = ft_calloc(count + 1, sizeof(char))))
		return (NULL);
	while (i < count)
	{
		if(s[i] == 39 || s[i] == 34 || s[i] == '$')
		{
			res = ft_exception(s, lst, data, &i);
			str = ft_strjoin_free(str, res, 3);
			while(str[j])
				j++;
		}
		else
			str[j++] = s[i];
		i++;
	}
	str[j++] = '\0';
	return (str);
}

char **clean_loop(char **av, char *params, t_env_lst *lst, int index, t_data *data)
{
	int j;

	j = 0;
	while (params[index])
	{
		if (params[index] == ' ')
		{
			if (index != 0)
				av[j++] = ft_str(params, index, lst, data);
			params = params + index + 1;
			index = -1;
		}
		else if (params[index + 1] == 0)
			av[j++] = ft_str(params, index + 1, lst, data);
		index++;
	}
	av[j] = NULL;
	return (av);
}

char	**clean_params(char *params, t_env_lst *lst, t_data *data)
{
	char **av;

	if (!(av = ft_calloc((c_p(params) + 1), sizeof(char *))))
		return (NULL);

	return (clean_loop(av, params, lst, 0, data));
}
