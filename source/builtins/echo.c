#include "minishell.h"

int	ft_echo(t_msh *msh, char **argv, char **env)
{
	int	i;
	int	flag;

	(void)env;
	(void)msh;
	i = 1;
	flag = 1;
	if (argv[1])
	{
		if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
		{
			i++;
			flag = 0;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && ft_strlen(argv[i]) != 0)
				write(1, " ", 1);
			i++;
		}
	}
	if (flag)
		write(1, "\n", 1);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_echo(NULL, argv, NULL);
// 	return (1);
// }