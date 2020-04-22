#include "../../../include/minishell.h"

int		count_env(char *params, int index , int c_env,t_env_lst *lst)
{
	params = params + index;
	while(lst)
	{
		if(ft_memcmp(params, lst->name, c_env) == 0)
		{
			printf("ok\n");
			return (ft_strlen(lst->value));
		}
		lst = lst->next;
	}
	return (2);
}

int		count_qchar(char *params, t_env_lst *lst, int quote_type, int index)
{
	int count;
	int c_env;
	int i;

	count = 0;
	i = 0;
	while(i < index)
	{
		if (params[i] == '$' && quote_type == 34)
		{
			c_env = 0;
			i++;
			while(params[i] != 34 && params[i + 1] != ' ' &&
				params[i + 1] != '\0')
			{
				c_env++;
				i++;
			}
			count += count_env(params, i - c_env, c_env, lst);
		}
		count++;
		i++;
	}
	return (count);
}


char	*ft_quote(char *params, int index, t_env_lst *lst)
{
	int n;
	int quote_type;

	quote_type = params[index];
	n = count_qchar(params, lst, quote_type, index);
	printf("env: %d\n", n);
	return (NULL);
}
