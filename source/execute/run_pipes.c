#include "minishell.h"

/*
**		@brief		runs command one by one
*/
void	run_commands_via_pipes(t_msh *msh)
{
	t_cmnd	*curr;

	curr = msh->lst_cmnd;
	while (curr)
	{
		curr->arg = ft_lst_get_array(curr->lst_arg);
		if (curr->next)
		{
			if (pipe(curr->pipe_fd) < 0)
				return (ft_raise_error(NULL, NULL));
			curr->out = curr->pipe_fd[1];
			curr->next->in = curr->pipe_fd[0];
			run_one_cmnd(msh, curr);
		}
		else
			run_one_cmnd_last(msh, curr);
		curr = curr->next;
	}
	wait_all_pipes(msh);
}

/*
**		@brief		runs the command, no last in the pipes chain 	
*/
void	run_one_cmnd(t_msh *msh, t_cmnd *cmnd)
{
	cmnd->pid = fork();
	if (!cmnd->pid)
	{
		if (cmnd->next)
			close(cmnd->next->in);
		if (!get_redirects(msh, cmnd, true))
		{
			if (is_builtin(msh, cmnd->arg[0]))
			{
				run_builtin(msh, cmnd, cmnd->arg[0]);
				exit(g_status);
			}
			else
				run_command(msh, cmnd);
		}
	}
	if (cmnd->in != STDIN)
		close(cmnd->in);
	if (cmnd->out != STDOUT)
		close(cmnd->out);
}

/*
**		@brief		runs the last (or only) command in the pipes chain 
*/
void	run_one_cmnd_last(t_msh *msh, t_cmnd *cmnd)
{
	save_stnd_io(msh);
	ft_signal();
	get_redirects(msh, cmnd, false);
	if (!g_status)
	{
		if (is_builtin(msh, cmnd->arg[0]))
			run_builtin(msh, cmnd, cmnd->arg[0]);
		else
		{
			cmnd->pid = fork();
			if (!cmnd->pid)
				run_command(msh, cmnd);
			close(STDIN);
			waitpid(cmnd->pid, &g_status, 0);
			g_status = WEXITSTATUS(g_status);
		}
	}
	restore_stnd_io(msh);
}

/*
**		@brief		waiting for all forks to end their work
*/
void	wait_all_pipes(t_msh *msh)
{
	t_cmnd	*cmnd;

	cmnd = msh->lst_cmnd;
	while (cmnd && cmnd->next)
	{
		if (cmnd->pid)
			waitpid(cmnd->pid, &g_status, 0);
		cmnd = cmnd->next;
	}
}
