#include "minishell.h"

int	ft_unset(char **argv, t_msh *msh)
{
	t_list	*env;
	t_list	*tmp;
	int		i;

	i = 1;
	env = msh->env;
	if (argv[1] == NULL)
		return (OK);
	while(argv[i])
	{
		env = msh->env;
		while(env && env->next)
		{
			remove_elem_from_envp(msh, argv[i]);
			env = env->next;
		}
		i++;
	}
	return (OK);
}