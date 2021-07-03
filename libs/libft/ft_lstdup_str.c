#include "libft.h"

/*
 * @brief	create new string from the hole list!
 * 
 * @param 	pointer to lst 
 * @return 	char*	new string
 */
char *ft_lstdup_str(t_list *lst)
{
	size_t	i;
	size_t	size_string;
	char	*new_str;
	t_list	*cur;

	size_string = 1;
	cur = lst;
	while (cur)
	{
		size_string += ft_strlen(cur->val);
		cur = cur->next;
	}
	new_str = ft_calloc(size_string, sizeof(*new_str));
	if (!new_str)
		return (NULL);
	i = 0;
	while (lst)
	{
		ft_memcpy(new_str + i, lst->val, ft_strlen(lst->val));
		i += ft_strlen(lst->val);
		lst = lst->next;
	}
	return (new_str);
}
