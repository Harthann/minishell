#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		if (fg_process > -1)
			kill(fg_process, signal);
		if (signal == SIGQUIT && fg_process > -1)
			write(1, "Exit (core dumped)", 18);
		write(0, "\n", 1);
	}
	else
		printf("Received another signal\n");
}