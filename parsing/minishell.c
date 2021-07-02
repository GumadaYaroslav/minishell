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
		str = readline("msh> ");
		add_history(str);
		parsing_by_words(&msh, str);
		// printf("|%s|\n", str);
		
		printf("-------------\n");
		// test_print_arr(new_arr);
		// printf("new_str=%s\n", ft_lstdup_str(lst));	
	}
}

void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp)
{
	size_t	i;
	
	msh->lst_env = NULL;
	i = 0;
	while (envp[i])
		ft_lstadd_front(&msh->lst_env, ft_lstnew(ft_strdup(envp[i++])));
	msh->env = ft_lst_get_array(msh->lst_env);
	msh->cmnd = NULL;
}
