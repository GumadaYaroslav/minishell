#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_msh	msh;

	inicialise_struct(&msh, argc, argv, envp);



	char *str;
	t_list *lst;
	lst = NULL;

	while (true)
	{
		str = readline("mshell> ");
		add_history(str);
		// parcing(str);
		// printf("|%s|\n", str);
		char **spl = ft_split(str, ' ');

		for (int i = 0; spl[i]; i++)
			ft_lstadd_front(&lst, ft_lstnew(ft_strdup(spl[i])));
		
		char **new_arr = ft_lst_get_array(lst);
		
		printf("-------------\n");
		test_print_arr(new_arr);
		printf("new_str=%s\n", ft_lstdup_str(lst));

		
			
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

t_cmnd	*new_command(t_msh *msh, size_t ind)
{
	t_cmnd	*new_cmnd;

	new_cmnd = malloc(sizeof(*new_cmnd));
	if (!new_cmnd)
		ft_raise_error(NULL, NULL);
	
	new_cmnd->ind = ind;
	new_cmnd->lst_arg = NULL;
	new_cmnd->arg = NULL;
	new_cmnd->l_arrow = NULL;
	new_cmnd->dl_arrow = NULL;
	new_cmnd->r_arrow = NULL;
	new_cmnd->dr_arrow = NULL;
	new_cmnd->next = NULL;

	return new_cmnd;
}


void	parcing(t_msh *msh, char *s)
{
	size_t	i;
	// t_flag	fl;
	t_cmnd	*cmnd;
	bool	empty_cmnd;

	t_cmnd = new_command(msh, 0);
	empty_cmnd = true;
	i = 0;
	while(s[i])
	{
		if (ft_ch_in_str(s[i], ' \t'))
		{
			i++;
			continue ;
		}
		if (s[i] == '|')
		{
			if (empty_cmnd)
				ft_raise_error("syntax error near unexpected token '|'", NULL);
			empty_cmnd = true;

		}
		
		if (s[i] == '<')
		{
			if (s[i] == '<')
			{

			}
			fl.quote = !fl.quote;
		else if (s[i])
		i++;
		
	}
}