#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		if (child_process > -1)
			kill(child_process, signal);
		if (signal == SIGINT)
			write(0, "\n", 1);
	}
	else
		printf("Received another signal\n");
}