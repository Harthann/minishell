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

char *ft_str(const char *s, int count)
{
	char *str;
	int i;

	i = 0;
	if (!(str = ft_calloc(count + 1, sizeof(char))))
		return (NULL);
	while (i < count)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**clean_params(char *params)
{
//	int n;
	int index;
	int j;
	char **av;

//	n = count_params(*params);
	index = 0;
	j = 0;
//	printf("params numbers: %d\n", n);
	if (!(av = ft_calloc(c_p(params) + 1, sizeof(char *))))
		return (NULL);
	while (params[index])
	{
		if (params[index] == ' ' || params[index] == '|')
		{
			if (index != 0)
				av[j++] = ft_str(params, index);
//			if (params[index] == '|')
//				av[j++] = ft_pipe();
			params = params + index + 1;
			index = -1;
		}
		else if (params[index + 1] == 0)
			av[j++] = ft_str(params, index + 1);
		index++;
	}
	av[j++] = NULL;
	return (av);
}
