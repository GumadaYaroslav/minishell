#include "minishell.h"

static	void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ft_putstr_fd(MSH_AVE, 1);
	rl_redisplay();
	g_status = 130;
}

void	ft_signal_child_process(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}
