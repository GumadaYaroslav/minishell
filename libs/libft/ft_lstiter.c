#include "libft.h"

/*
**	@brief	iterates the list and applies the function to the content
**	
**	@param	lst		pointer to the list
**	@param	f		function to change content
*/
void	ft_lstiter(t_list *lst, void (*f)(char *))
{
	while (lst)
	{
		f(lst->val);
		lst = lst->next;
	}
}
