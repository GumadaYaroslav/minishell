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
		str = readline("\033[32mmsh$ \033[0m");
		add_history(str);

		if (!parsing(&msh, str))
		{
			run_commands_via_pipes(&msh);
			wait_all_pipes(&msh);
		}	
		
		msh.old_status = msh.status;
		msh.status = 0;
		msh.lst_cmnd = NULL;
		// ft_lstclear(&msh.lst_cmnd);
			// todo clear


		
	}
}
