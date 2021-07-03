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
		parsing_by_words(&msh, str);
		// printf("|%s|\n", str);
		
		printf("-------------\n");
		test_print_command(msh.cmnd);
		msh.cmnd = NULL; // todo clear
		// test_print_arr(new_arr);
		// printf("new_str=%s\n", ft_lstdup_str(lst));	
	}
}

