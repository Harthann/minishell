#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		// printf("Signal received\n");
		kill(child_process, signal);
	}
	else
		printf("Received another signal\n");
}