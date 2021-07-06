#include "minishell.h"

int	ft_env(char **argv, char **env, t_msh *msh)
{
	t_list *inv;

	inv = msh->lst_env;
	(void)argv;
	(void)env;
	while(inv->next)
	{
		ft_putstr_fd(inv->val, 1);
		inv = inv->next;
	}
	ft_putstr_fd(inv->val, 1);
}