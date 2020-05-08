#include "minishell.h"

char	*prs_mem(int fd)
{
	char *buf;
	char *cumul;
	char *mem;

	cumul = NULL;
	if(!(buf = ft_calloc(100, sizeof(char))))
		return (NULL);
	while (read(fd, buf, 100)  != 0)
	{
//		printf("iii");
		mem = cumul;
		cumul = ft_strjoin(cumul, buf);
		free(mem);
	}
	free(buf);
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
