/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:12:25 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/07 16:27:41 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_signal_in_child(void)
{
	// signal(SIGCHLD, SIG_DFL);
	// signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static	void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

static	void	ft_signal_pipes(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", 2);
	else
		ft_putendl_fd("Quit: 3", 2);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_main(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_run_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}