#include "minishell.h"

char *prs_mem(int fd)
{
	char *buf;
	char *cumul;
//	char *mem;

	cumul = NULL;
	if(!(buf = ft_calloc(100, sizeof(char))))
		return (NULL);
/*	while (read(fd, buf, 100)  != 0)
	{
		printf("iii");
		mem = cumul;
		cumul = ft_strjoin(cumul, buf);
		free(mem);
	}
	free(buf);
	close(fd); */
	read(fd, buf, 10);
	printf("buf : [%s]\n", buf);
	return (cumul);
}
