#include "minishell.h"

static	void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	// ft_putstr_fd(MSH_AVE, 1);
	// ft_putstr_fd("^C", 1);
	// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_redisplay();
	// write(1, "  ", 2);
	// rl_replace_line("", 0);
	write(1, "\n", 1);
	ft_putstr_fd(MSH_AVE, 1);
	rl_redisplay();
	g_status = 130;
}

// static	void	ft_signal_quit(int sig)
// {
// 	(void)sig;
// 	write(1, "\b\b", 2);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	rl_replace_line("", 0);
// 	write(1, "  ", 2);
// 	// write(1, "\n", 1);
// 	// rl_redisplay();
// 	// ft_putstr_fd(MSH_AVE, 1);
// 	g_status = 131;
// }

void			ft_signal_child_process(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}