#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
		printf("Signal received\n");
	else
		printf("Received another signal\n");
}