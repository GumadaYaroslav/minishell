#include "minishell.h"

void	save_stnd_io(t_msh *msh)
{
	msh->old_in = dup(STDIN);
	msh->old_out = dup(STDOUT);
	if (msh->old_in < 0 || msh->old_out < 0)
		ft_raise_error(msh, 0, 0);
}

void	restore_stnd_io(t_msh *msh)
{
	close(STDIN);
	close(STDOUT);
	if (dup2(msh->old_in, STDIN) < 0)
		ft_raise_error(msh, 0, 0);
	if (dup2(msh->old_out, STDOUT) < 0)
		ft_raise_error(msh, 0, 0);
}

void	dups_input_output(t_msh *msh, t_cmnd *cmnd)
{
	if (cmnd->in)
	{
		if (dup2(cmnd->in, STDIN) < 0) // заворачиваем вывод для непервого пайпа
		{
			if (cmnd->is_fork)
				ft_critical_error(0, 0);
			return (ft_raise_error(msh, 0, 0));
		}
		close(cmnd->in);
	}
	if (cmnd->out)
	{
		if (dup2(cmnd->out, STDOUT) < 0) // заворачиваем вывод для непервого пайпа
		{
			if (cmnd->is_fork)
				ft_critical_error(0, 0);
			return (ft_raise_error(msh, 0, 0));
		}
		close(cmnd->out);
	} 
}

