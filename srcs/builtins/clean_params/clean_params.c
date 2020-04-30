#include "../../../include/minishell.h"

int		c_p(char *params)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while(params[i])
	{
		if(params[i] == ' ' || params[i] == '|')
			n++;
		i++;
	}
	return (n);
}

char *ft_str(const char *s, int count, t_env_lst *lst)
{
	char *str;
	char *mem;
	char *res;
	int i;

	i = 0;
	if (!(str = ft_calloc(count + 1, sizeof(char))))
		return (NULL);
	while (i < count && s[i] != '$')
	{
		str[i] = s[i];
		i++;
	}
	if(s[i] == '$')
	{
		mem = env_value((char *)s, i, lst);
		res = ft_strjoin(str, mem);
		free(mem);
		free(str);
		return (res);
	}
	str[i] = '\0';
	return (str);
}

char **clean_loop(char **av, char *params, t_env_lst *lst, int index)
{
	int j;

	j = 0;
	while (params[index])
	{
		if ((params[index] == 39 || params[index] == 34)
				&& (params[index + 1] == ' ' || params[index + 1] == 0))
		{
			av[j++] = ft_quote(params, index, lst);
			params = params + index + 1;
			index = -1;
		}
		else if (params[index] == ' ')
		{
			if (index != 0)
				av[j++] = ft_str(params, index, lst);
			params = params + index + 1;
			index = -1;
		}
		else if (params[index + 1] == 0)
			av[j++] = ft_str(params, index + 1, lst);
		index++;
	}
	av[j++] = NULL;
	return (av);
}

char	**clean_params(char *params, t_env_lst *lst)
{
	char **av;

	if (!(av = ft_calloc(c_p(params) + 1, sizeof(char *))))
		return (NULL);
	return (clean_loop(av, params, lst, 0));
}
