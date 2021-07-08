#include "minishell.h"

void	run_commands_via_pipes(t_msh *msh)
{
	t_cmnd	*curr;

	curr = msh->lst_cmnd;
	// run_cmnd_first(msh, curr);
	while (curr)
	{
		if (curr->next)
		{
			printf("run command %s\n", curr->lst_arg->val);
			if (pipe(curr->pipe_fd) < 0)
				ft_raise_error(NULL, NULL); // здесь нужно переделать на функцию явного брэйка и возврата в мэйн
			curr->out = curr->pipe_fd[1];
			curr->next->in = curr->pipe_fd[0];	
			run_one_cmnd(msh, curr);
		}
		else
		{
			printf("run last %s\n", curr->lst_arg->val);
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
	get_redirects(msh, cmnd);
	if (cmnd->in)
		close(cmnd->in);
	cmnd->pid = fork();
	if (!cmnd->pid)
		run_command(msh, cmnd);
	
	waitpid(cmnd->pid, &cmnd->status, 0);
	printf("status last pid = %d\n", cmnd->pid);
	restore_stnd_io(msh);
}




 
void	run_command(t_msh *msh, t_cmnd *cmnd)
{
	char	**paths;
	char	*name;

	if (!cmnd->lst_arg)
		return ;
	paths = get_splited_path(msh);
	cmnd->arg = ft_lst_get_array(cmnd->lst_arg);
	name = cmnd->arg[0];
	while (gen_next_path(cmnd->arg, paths, name))
	{
		if (!access(cmnd->arg[0], F_OK)) // TODO! forbidden func
		{
			if (!access(cmnd->arg[0], X_OK))
			{
				printf("execve %s\n", cmnd->arg[0]);
				execve(cmnd->arg[0], cmnd->arg, msh->env);

			}
			break ;
		}
	}
	ft_raise_error(ft_strjoin("Command not found: ", name), NULL);
}
