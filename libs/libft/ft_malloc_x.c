#include "libft.h"
#include <sys/errno.h>

/*
**		@brief		midification for instantly exit if not allocate		
*/
void	*ft_malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putendl_fd("Critical error: cannot allocate memmory", 2);
		exit(errno);
	}
	else
		return (ptr);
}
