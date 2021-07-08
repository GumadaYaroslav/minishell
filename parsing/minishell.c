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
		printf("wait new command\n");
		str = readline("msh$ ");
		add_history(str);

		parsing_by_words(&msh, str);	
		printf("-------------\n");
		test_print_command(msh.lst_cmnd);

		run_commands_via_pipes(&msh);

		msh.lst_cmnd = NULL;
		// ft_lstclear(&msh.lst_cmnd);
			// todo clear


		
	}
}
