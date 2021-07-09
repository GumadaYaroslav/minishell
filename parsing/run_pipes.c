#include "minishell.h"

void	run_commands_via_pipes(t_msh *msh)
{
	t_cmnd	*curr;

	curr = msh->lst_cmnd;
	while (curr)
	{
		curr->arg = ft_lst_get_array(curr->lst_arg);
		if (curr->next)
		{
			if (curr->lst_arg)
				printos("run one", curr->lst_arg->val);
			if (pipe(curr->pipe_fd) < 0)
				ft_raise_error(NULL, NULL); // здесь нужно переделать на функцию явного брэйка и возврата в мэйн
			curr->out = curr->pipe_fd[1];
			curr->next->in = curr->pipe_fd[0];
			run_one_cmnd(msh, curr);
		}
		else
		{
			
				printos("run last", curr->lst_arg->val);
			run_one_cmnd_last(msh, curr);
		}
		curr = curr->next;
	}
}

void	run_one_cmnd(t_msh *msh, t_cmnd *cmnd)
{
	cmnd->pid = fork();
	if (!cmnd->pid)
	{
		get_redirects(msh, cmnd);
		if (is_builtin(msh, cmnd->arg[0]))
		{
			printos("Builtin", cmnd->arg[0]);
			run_builtin(msh, cmnd, cmnd->arg[0]);
			exit(cmnd->status);
		}
		else
			run_command(msh, cmnd);
	}
	else
	{
		if (cmnd->in)
			close(cmnd->in); // это предыдущий выход пайпа, он работает в форфке и можем  гасить
		if (cmnd->out) // для не ласта
			close(cmnd->out);	// это текущий ввод в пайп. аналогично гасим
	}
}


void	run_one_cmnd_last(t_msh *msh, t_cmnd *cmnd)
{
	save_stnd_io(msh);
	get_redirects(msh, cmnd); // need adds checks values
	if (!cmnd->status) //
		if (is_builtin(msh, cmnd->arg[0]))
		{
			printos("Builtin", cmnd->arg[0]);
			run_builtin(msh, cmnd, cmnd->arg[0]);
		}
		else
		{
			cmnd->pid = fork();
			if (!cmnd->pid)
				run_command(msh, cmnd);
			waitpid(cmnd->pid, &cmnd->status, 0);
		}
	restore_stnd_io(msh); // todo: checks used fds
	printod("status last pid", cmnd->pid);
	
}

void	wait_all_pipes(t_msh *msh)
{
	t_cmnd	*cmnd;

	cmnd = msh->lst_cmnd;
	printos(0, "wait pids");
	while(cmnd && cmnd->next)
	{
		waitpid(cmnd->pid, &cmnd->status, 0);
		cmnd = cmnd->next;
	}
}