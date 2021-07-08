#include "minishell.h"

void	save_stnd_io(t_msh *msh)
{
	msh->old_in = dup(STDIN);
	msh->old_out = dup(STDOUT);
}

void	restore_stnd_io(t_msh *msh)
{
	dup2(msh->old_in, STDIN);
	dup2(msh->old_out, STDOUT);
	// todo clear or close?
}

void	dups_input_output(t_msh *msh, t_cmnd *cmnd)
{
	if (cmnd->in)
	{
		if (dup2(cmnd->in, STDIN) < 0) // заворачиваем вывод для непервого пайпа
			ft_raise_error(NULL, NULL);
		close(cmnd->in);
	}
	if (cmnd->out)
	{
		if (dup2(cmnd->out, STDOUT) < 0) // заворачиваем вывод для непервого пайпа
			ft_raise_error(NULL, NULL);
		close(cmnd->out);
	} 
}

