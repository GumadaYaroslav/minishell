#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_msh	msh;
	char *str;

	inicialise_struct(&msh, argc, argv, envp);
	while (true)
	{
		str = readline("msh$ ");
		add_history(str);
		msh.pid = fork();
		if (!msh.pid)
		{
			parsing_by_words(&msh, str);	
			printf("-------------\n");
			test_print_command(msh.lst_cmnd);
			 // todo clear. хотя дальше все равно эксит и чего мозги ебать
			exit(0); // или не ноль. хуй знает
		}
		wait(0);
	}
}

