#include "../../../include/minishell.h"

int		count_annexe(char *params, int i)
{
	if((params[i] == ' ' && i != 0 && params[i - 1] != ' '
	&& params[i - 1] != 39 && params[i - 1] != 34)
	|| (params[i + 1] == '\0' && params[i] !=  ' '))
		return (1);
	return (0);
}

int		count_params(char *params)
{
	int n;
	int i;
	int mem;

	i = 0;
	n = 0;
	while(params[i])
	{
		n = (count_annexe(params, i) == 1) ? n + 1 : n;
		if(params[i] == 34 || params[i] == 39)
		{
			mem = params[i];
			n = (i != 0 && params[i - 1] != ' ') ? n - 1 : n;
			i++;
			while(params[i] != mem && params[i])
				i++;
			if(i != 0 && (params[i + 1] != ' ' && params[i + 1] != '\0'))
				n--;
			n++;
		}
		n = (params[i] == '|' && params[i - 1] != ' ') ? n + 1 : n;
		i++;
	}
	return (n);
}


void	clean_params(char **params)
{
	int n;
	printf("%s\n", *params);
	n = count_params(*params);
	printf("params numbers: %d\n", n);
}
