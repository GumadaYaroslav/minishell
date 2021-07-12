#include "minishell.h"

void	get_redirects(t_msh *msh, t_cmnd *cmnd, bool is_fork)
{
	t_list	*redirect;

	redirect = cmnd->redirects;
	while (redirect)
	{
		if (!ft_strncmp(redirect->val, "<<", 2))
			;
		else if (!ft_strncmp(redirect->val, "<", 1))
			;
		else if (!ft_strncmp(redirect->val, ">>", 2))
			;
		else if (!ft_strncmp(redirect->val, ">", 1))
			;
		redirect = redirect->next;
	}
	dups_input_output(msh, cmnd, is_fork);
}

void double_left_arrow(t_msh *msh, t_cmnd *cmnd, bool is_fork)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
	{
		if (is_fork)
			ft_critical_error(NULL, NULL);
		else
			ft_raise_error(msh, NULL, NULL);
	}
	pid = fork();
	if (pid)
	{
		wait(0);
		cmnd->in = fd[0];
		close(fd[1]);
	}
	else
		double_left_arrow_read(p, fd);
}

void	double_left_arrow_read(t_msh *msh, t_cmnd *cmnd, bool is_fork)
{
	char	*line;
	int		res;

	res = 1;
	while (res)
	{
		ft_putstr_fd("heredoc> ", 1);
		res = ne_gnl(0, &line, p->stop_word);
		if (res < 0)
			ft_raise_error(NULL, NULL);
		if (res)
			ft_putendl_fd(line, fd[1]);
		free(line);
	}
	p->infile = NULL;
	close(fd[0]);
	close(fd[1]);
	exit(0);
}
