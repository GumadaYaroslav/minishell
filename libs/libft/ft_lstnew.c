#include "libft.h"

/*
**	@brief	create new list element
**	
**	@param	val		element content
**	@return	t_list*	pointer to new element or NULL
*/
t_list	*ft_lstnew(char *val)
{
	t_list	*elem;

	elem = ft_malloc_x(sizeof(*elem));
	if (elem)
	{
		elem->val = val;
		elem->next = NULL;
	}
	return (elem);
}
