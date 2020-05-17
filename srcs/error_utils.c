#include "minishell.h"

void	error_child(int fd)
{
	char *buf;

	if(!(buf = ft_calloc(4, sizeof(char))))
		buf = 0;
	read(fd, buf, 4);
	errno = ft_atoi(buf);
	free(buf);
	close(fd);
}

void	last_return(t_data *data, char *m)
{
	if(errno == 0 && *m != '\0')
	{
		ft_putstr_fd(m, 2);
		data->last_return = 127;
	}
	else if(errno != 0)
		data->last_return = 127;
	else
		data->last_return = 0;
}

int		length(char **params)
{
	int count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}
