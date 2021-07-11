#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;
	char *str;

	inicialise_struct(&msh, argc, argv, envp);
	while (true)
	{
		str = readline("\033[32mmsh$ \033[0m");
		add_history(str);

		if (!parsing(&msh, str))
		{
			run_commands_via_pipes(&msh);
		}	
		printos(0, "before clean");
		cleaning(&msh, str);	
	}
}

void	cleaning(t_msh *msh, char *str)
{
	free(str);
	ft_lstclear_cmnds(&msh->lst_cmnd);
	msh->lst_cmnd = NULL; // can be delete
	msh->old_status = msh->status;
	msh->status = 0;
}

void	ft_lstclear_cmnds(t_cmnd **cmnd)
{
	t_cmnd	*next;

	while (*cmnd)
	{
		next = (*cmnd)->next;
		ft_lstclear(&(*cmnd)->lst_arg);
		ft_lstclear(&(*cmnd)->redirects);
		if ((*cmnd)->arg)
			ft_split_free((*cmnd)->arg);
		(*cmnd)->arg = NULL;
		free(*cmnd);
		*cmnd = next;
	}
}