#include "../../../include/minishell.h"

int		count_char(char *str)
{
	int count;

	count = 0;
	while(str[count] != ' ' && str[count] != '$' && str[count])
		count++;
	return (count);
}


char	*env_value(char *str, int index, t_env_lst *lst)
{
	int n;

	str = str + index + 1;
	n = count_char(str);
	while(lst)
	{
		if(ft_memcmp(str, lst->name, n) == 0)
			return (ft_strdup(lst->value));
		lst = lst->next;
	}
	return (ft_strdup("\0"));
}


int		count_char2(char *str)
{
	int count;

	count = 0;
	while(str[count] != 34 && str[count])
		count++;
	return (count);
}


char	*env_value2(char *str, t_env_lst *lst)
{
	int n;

	n = count_char2(str);
	while(lst)
	{
		if(ft_memcmp(str, lst->name, n) == 0)
			return (ft_strdup(lst->value));
		lst = lst->next;
	}
	return (ft_strdup("\n"));
}
