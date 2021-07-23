#include <minishell.h>

// void			ft_signal_cltr_c(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	// ft_print_shell();
// 	ft_putstr_fd("\033[36m", 1);
// 	ft_putstr_fd("minishell", 1);
// 	ft_putstr_fd("\033[37m", 1);
// 	if (g_status == 0)
// 	{
// 		ft_putstr_fd("\033[32m", 1);
// 		ft_putstr_fd("(o-_-o)", 1);
// 		ft_putstr_fd("\033[37m", 1);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\033[31m", 1);
// 		ft_putstr_fd("(＞-＜)", 1);
// 		ft_putstr_fd("\033[37m", 1);
// 	}
// 	g_status = 1;
// 	ft_putstr_fd("\033[36m", 1);
// 	ft_putstr_fd("$> ", 1);
// 	ft_putstr_fd("\033[37m", 1);
// }

void			ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}