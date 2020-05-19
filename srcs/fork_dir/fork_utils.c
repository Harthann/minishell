#include "minishell.h"

void	prs_mem2(char **cumul, char *line)
{
	char *mem;

	mem = *cumul;
	*cumul =  ft_strjoin(*cumul, line);
	free(mem);
}

char	*prs_mem(int fd)
{
	char	*line;
	char	*cumul;
	int		ret;

	cumul = NULL;
	ret = 1;
	line = NULL;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		prs_mem2(&cumul, line);
		if (ret > 0)
			prs_mem2(&cumul, "\n");
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	return (cumul);
}

int		left_redir(t_cmd *list)
{
	if (!list)
		return (0);
	else if(ft_memcmp(list->command, "<", 1) == 0)
		return (1);
	else
		return (0);
}

int		right_redir(t_cmd *list)
{
	if (!list)
		return (0);
	else if (ft_memcmp(list->command, ">", 1) == 0
			|| ft_memcmp(list->command, ">>", 2) == 0)
		return (1);
	else
		return (0);
}

int		check_pipe(t_cmd *list)
{
	if (!list)
		return (0);
	else if (ft_memcmp(list->command, "|", 1) == 0)
		return (1);
	else
		return (0);
}
