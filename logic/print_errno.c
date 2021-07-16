#include "minishell.h"

int print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(1, "\n", 1);
	return (errno);
}