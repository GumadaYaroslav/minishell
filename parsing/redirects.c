#include "minishell.h"

/*
**	@brief	runs funcstions for redirects list
**	
**	@param	msh		main structure
**	@param	cmnd	command
**	@param	is_fork	true if it's runned in fork
**	@return	int		0 if no error
*/
int	get_redirects(t_msh *msh, t_cmnd *cmnd, bool is_fork)
{
	t_list	*redirect;
	
	cmnd->is_fork = is_fork;
	redirect = cmnd->redirects;
	while (redirect && !msh->status)
	{
		if (!ft_strncmp(redirect->val, "<<", 2))
			double_left_arrow(msh, cmnd, redirect->val + 2);
		else if (!ft_strncmp(redirect->val, "<", 1))
			redirect_open_file(msh, cmnd, redirect->val + 1, L_ARR);
		else if (!ft_strncmp(redirect->val, ">>", 2))
			redirect_open_file(msh, cmnd, redirect->val + 2, R_D_ARR);
		else if (!ft_strncmp(redirect->val, ">", 1))
			redirect_open_file(msh, cmnd, redirect->val + 1, R_ARR);
		redirect = redirect->next;
	}
	if (!msh->status)
		dups_input_output(msh, cmnd);
	return (msh->status);
}

/*
**	@brief	corutine for <<. 
**			Reads lines from stdin to stop word
*/
void double_left_arrow(t_msh *msh, t_cmnd *cmnd, char *stop_word)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
	{
		if (cmnd->is_fork)
			ft_critical_error(NULL, NULL);
		else
			ft_raise_error(msh, NULL, NULL);
	}
	pid = fork();
	if (pid)
	{
		waitpid(pid, 0, 0);
		cmnd->in = fd[0];
		close(fd[1]);
	}
	else
	{
		close(fd[0]);
		cmnd->out = fd[1];
		double_left_arrow_read(msh, cmnd, stop_word);
	}
}


void	double_left_arrow_read(t_msh *msh, t_cmnd *cmnd, char *stop_word)
{
	char	*line;

	(void)msh;
	while (true)
	{
		line = readline("> ");
		if (!ft_strncmp(line, stop_word, ft_strlen(stop_word) + 1))
			break ;
		ft_putendl_fd(line, cmnd->out);
		free(line);
	}
	close(cmnd->out);
	exit(0);
}

void	redirect_open_file(t_msh *msh, t_cmnd *cmnd, char *fname, int mode)
{
	if (mode == L_ARR)
	{
		if (cmnd->in)
			close(cmnd->in);
		cmnd->in = open(fname, O_RDONLY);
	}
	else
	{
		if (cmnd->out)
			close(cmnd->out);
		if (mode == R_ARR)
			cmnd->out = open(fname, O_RDWR | O_CREAT | O_TRUNC, 00774);
		else
			cmnd->out = open(fname, O_WRONLY | O_APPEND | O_CREAT, 00774);
	}
	if (cmnd->in < 0 || cmnd->out < 0)
	{
		if (cmnd->is_fork)
			ft_critical_error(NULL, fname);
		else
			ft_raise_error(msh, NULL, fname);
	}
}