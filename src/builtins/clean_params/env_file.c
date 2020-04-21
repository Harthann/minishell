#include "../../../include/minishell.h"

int		count_char(char *str)
{
	int count;

	count = 0;
	while(str[count] != ' ' && str[count])
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
	return (ft_strdup("\n"));
}
