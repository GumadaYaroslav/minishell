#include <minishell.h>

void			ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// ft_print_shell();
	ft_putstr_fd("\033[36m", 1);
	ft_putstr_fd("minishell", 1);
	ft_putstr_fd("\033[37m", 1);
	if (g_status == 0)
	{
		ft_putstr_fd("\033[32m", 1);
		ft_putstr_fd("(o-_-o)", 1);
		ft_putstr_fd("\033[37m", 1);
	}
	else
	{
		ft_putstr_fd("\033[31m", 1);
		ft_putstr_fd("(＞-＜)", 1);
		ft_putstr_fd("\033[37m", 1);
	}
	g_status = 1;
	ft_putstr_fd("\033[36m", 1);
	ft_putstr_fd("$> ", 1);
	ft_putstr_fd("\033[37m", 1);
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

static	void	ft_sigterm(int sig)
{
	(void)sig;
}

static	void	ft_signal_sigchld(int sig)
{
	(void)sig;
}

void			ft_signal(void)
{
	signal(SIGQUIT, ft_signal_quit);
	signal(SIGCHLD, ft_signal_sigchld);
	signal(SIGTERM, ft_sigterm);
}