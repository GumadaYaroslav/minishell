#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;


	// int fd = open("out", O_RDWR | O_CREAT | O_TRUNC, 00774);
	// int pid = fork();
	// char *run[] = {"/bin/rm", "out", 0};
	// if (pid)
	// {
	// 	wait(0);
	// 	write(fd, "huy nam a ne write\n", 20);
	// }
	// else
	// {
	// 	execve(run[0], run, 0);
	// 	printf("error\n");
	// }

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

void	parcing(char *s)
{
	size_t	i;
	t_flag	fl;

	i = 0;
	while(s[i])
	{
		if (s[i] == '\'')
			fl.quote = !fl.quote;
		else if (s[i])
		i++;
		
	}
}