#include <minishell.h>

void	ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
