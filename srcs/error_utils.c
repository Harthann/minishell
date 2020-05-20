#include "minishell.h"

void	last_return(t_data *data, char *m)
{
	if (*m == '\0' && errno == 0)
		data->last_return = 0;
	else if (errno != 0)
		data->last_return = 127;
	else if (errno == 0 && *m != '\0')
	{
		ft_putstr_fd(m, 2);
		data->last_return = 127;
	}
	free(m);
}

int		length(char **params)
{
	int count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}
