#include "libft.h"

/*
**	@brief	finds element in the list by key
**	
**	@param	lst		pointer to begin of the list
**  @param	key		pointer to begin of value
**	@return	t_list*	pointer to the needed element or NULL
*/
t_list	*ft_lstfind(t_list *lst, char *key)
{
	while (lst)
	{
		if (!ft_strncmp(lst->val, key, ft_strlen(key)))
			break ;
		lst = lst->next;
	}
	return (lst);
}
