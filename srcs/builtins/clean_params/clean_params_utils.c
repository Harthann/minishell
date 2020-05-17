#include "minishell.h"

char *dollar_check(t_data *data, char *s, t_env_lst *lst, int index)
{
	if (s[index + 1] == '?')
		return (ft_itoa(data->last_return));
	else
		return (env_value(s, index, lst));
}
