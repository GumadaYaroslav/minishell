#include "libft.h"

/*
**	@brief	searches and pop element from list
**	
**	@param	lst		pointer  to poiner to list
**	@param	val		content for search
**	@return	t_list*	pointer to element
*/
t_list	*ft_lstpop_find(t_list **lst, char *key)
{
	t_list	*elem;
	t_list	*curr;

	elem = NULL;
	curr = *lst;
	if (curr && !ft_strncmp(curr->val, key, ft_strlen(key)))
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		return (elem);
	}
	while (curr && curr->next)
	{
		if (!ft_strncmp(curr->next->val, key, ft_strlen(key)))
		{
			elem = curr->next;
			curr->next = curr->next->next;
			elem->next = NULL;
			break ;
		}
		curr = curr->next;
	}
	return (elem);
}
