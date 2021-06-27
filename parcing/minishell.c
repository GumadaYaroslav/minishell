#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *str;

	str = readline("mshell> ");
	add_history(str);
	printf("|%s|\n", str);

}
