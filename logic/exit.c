#include "minishell.h"

u_int8_t atoi_overflow(const char *str)
{
	int         i;
	int         minus;
	u_int64_t   num;

	i = 0;
	minus = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	return (num * minus);
}

static int	is_not_num(char *argv)
{
	int i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int ft_exit(char **argv, t_msh *msh)
{
	if (argv[1] == NULL)
		exit(0);
	if(is_not_num(argv[1]))

	exit(1);
	return (0);
}