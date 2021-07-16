#include "minishell.h"

/*
**		@brief		Hello world!
*/
int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;
	char *str;

	inicialise_struct(&msh, argc, argv, envp);
	ft_signal();
	while (true)
	{
		str = readline(MSH_AVE);
		ft_signal_child_process();
		if (!str)
			exit (0); // for CTRL+D
		if (ft_strlen(str))
			add_history(str);
		if (!parsing(&msh, str))
			run_commands_via_pipes(&msh);
		cleaning(&msh, str);
	}
}
