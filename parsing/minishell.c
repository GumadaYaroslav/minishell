#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_msh	msh;
	char *str;

	inicialise_struct(&msh, argc, argv, envp);
////MAIN
	while (true)
	{
		str = readline("msh$ ");
		add_history(str);

		parsing_by_words(&msh, str);	
		printf("-------------\n");
		test_print_command(msh.lst_cmnd);

		run_commands($msh)


		ft_lstclear(&msh.lst_cmnd);
			// todo clear


		
	}
}

void	run_commands(t_msh *msh)
{
	t_cmnd	*curr;

	curr = msh->lst_cmnd;
	while (curr)
	{
		if (curr->next)
			run_one_cmnd(msh, curr);
		else
			run_last_cmnd(msh, curr);
		curr = curr->next;
	}
}

void	run_one_cmnd(t_msh *msh, t_cmnd *cmnd)
{
	cmnd->pid = fork();
	if (!cmnd->pid)
	{
		if (pipe(cmnd->pipe_fd) < 0) // создаем новый пайп если это не последняя команда
			ft_raise_error(NULL, NULL);
		get_left_redirects(t_msh *msh, t_cmnd *cmnd)
	}
}

get_left_redirects(t_msh *msh, t_cmnd *cmnd)