#include "minishell.h"

int	ft_export(char **argv, t_msh *msh)
{
	int	i;

	i = 1;
	if(ft_split_len(argv) == 1)
		print_export(msh->env);
	while(argv[i])
	{
		insert_or_update_elem_from_envp(msh, argv[i]);
		i++;
	}
	return (0);
}