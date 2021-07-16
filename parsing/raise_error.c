#include "minishell.h"

/*
**	@brief	raises error message and exit from program
*/
void	ft_critical_error(char *msg, char *errno_msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(errno_msg);
	if (errno)
		exit (errno);
	else
		exit(1);
}

/*
**	@brief	raises error message and change error code
*/
void	ft_raise_error(char *msg, char *errno_msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(errno_msg);
	if (errno)
		g_status = errno;
	else
		g_status = 1;
}
