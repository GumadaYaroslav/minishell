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
		str = readline("\033[32mmsh$ \033[0m");
		add_history(str);

		parsing_by_words(&msh, str);	
		test_print_command(msh.lst_cmnd);

		run_commands_via_pipes(&msh);
		wait_all_pipes(&msh);

		msh.lst_cmnd = NULL;
		// ft_lstclear(&msh.lst_cmnd);
			// todo clear


		
	}
}
