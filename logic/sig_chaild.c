#include "minishell.h"

static	void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	ft_putstr_fd(MSH_AVE, 1);
	ft_putstr_fd("^C", 1);
	write(1, "\n", 1);
	ft_putstr_fd(MSH_AVE, 1);
	g_status = 130;
}

static	void	ft_signal_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
	g_status = 131;
	exit(0);
}

void			ft_signal_child_process(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, ft_signal_quit);
}