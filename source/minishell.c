#include "minishell.h"

int		g_status;

/*
**		@brief		Hello world!
*/
int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;
	char	*str;

	g_status = 0;
	rl_outstream = stderr;
	inicialise_struct(&msh, argc, argv, envp);
	ft_signal_child_process();
	while (true)
	{
		
		str = readline(MSH_AVE);
		if (!str)
		{
			// ft_putendl_fd("exit", 2);
			str = ft_strdup("exit");
		}
		if (ft_strlen(str))
			add_history(str);
		if (!parsing(&msh, str))
			run_commands_via_pipes(&msh);
		cleaning(&msh, str);

	}
}
