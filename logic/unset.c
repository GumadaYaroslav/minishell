#include "minishell.h"

int	ft_unset(char **argv, t_msh *msh)
{
	t_list	*env;
	int		i;

	i = 1;
	env = msh->lst_env;
	if (argv[1] == NULL)
		return (OK);
	while(argv[i])
	{
		env = msh->lst_env;
		while(env && env->next)
		{
			remove_elem_from_envp(msh, argv[i]);
			env = env->next;
		}
		i++;
	}
	return (OK);
}