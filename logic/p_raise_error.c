#include "minishell.h"

/*
**	@brief	raises error message and exit from program
**	
**	@param	s	pointer to string with error message
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
**	
**	@param	s	pointer to string with error message
*/
void	ft_raise_error(t_msh *msh, char *msg, char *errno_msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(errno_msg);
	if (errno)
		msh->status = errno;
	else
		msh->status = 1;
}

/*
**	@brief	checks if the program name starts from character '/'
**	
**	@param	s	pointer to string
**	@return	int	1 if is path
*/
int	ft_is_path(char *s)
{
	while (*s && !ft_isalnum(*s))
		if (*s++ == '/')
			return (1);
	return (0);
}
