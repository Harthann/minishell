#include "minishell.h"

char	*prs_mem(int fd)
{
	char *line;
	char *cumul;
	char *mem;
	int	ret;

	cumul = NULL;
	ret = 1;
//	if(!(buf = ft_calloc(100, sizeof(char))))
//		return (NULL);
	while (ret > 0)
	{
		
//		printf("iii");
		ret = get_next_line(fd, &line);
		mem = cumul;
		cumul = ft_strjoin(cumul, line);
		if(ret > 0)
		{
			free(mem);
			mem = cumul;
			cumul = ft_strjoin(cumul, "\n");
		}
		free(mem);
	}
	free(line);
	close(fd); 
//	read(fd, buf, 10);
//	printf("buf : [%s]\n", buf);
	return (cumul);
}

int		left_redir(t_cmd *list)
{
	if(!list)
		return (0);
	else if(ft_memcmp(list->command, "<", 1) == 0)
		return (1);
	else
		return (0);
}

int		right_redir(t_cmd *list)
{
	if(!list)
		return (0);
	else if(ft_memcmp(list->command, ">", 1) == 0
			|| ft_memcmp(list->command, ">>", 2) == 0)
		return (1);
	else
		return (0);
}
