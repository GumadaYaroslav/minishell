#include "libft.h"

/*
 * @brief	create new massive (like result ft_split) from list.
 * 			Starts from the last element of list!
 * 
 * @param 	pointer to lst 
 * @return 	char** new array
 */
char **ft_lst_get_array(t_list *lst)
{
	int		size_array;
	char	**arr;

	size_array = ft_lstsize(lst) + 1;
	arr = malloc(sizeof(*arr) * size_array);
	if (!arr)
		return (NULL);
	arr[--size_array] = NULL;
	while (lst)
	{
		arr[--size_array] = ft_strdup(lst->val);
		lst = lst->next;
	}
	return (arr);
}
