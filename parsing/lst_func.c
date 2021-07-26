#include "minishell.h"

/*
**	@brief	finds element in the list by key
**	
**	@param	lst		pointer to begin of the list
**  @param	key		pointer to begin of value
**	@return	t_list*	pointer to the needed element or NULL
*/
t_list	*ft_lstfind(t_list *lst, const char *key)
{
	size_t	key_len;

	key_len = ft_keylen(key);
	while (lst)
	{
		if (!ft_strncmp(lst->val, key, key_len) && lst->val[key_len] == '=')
			break ;
		lst = lst->next;
	}
	return (lst);
}

/*
**	@brief	searches and pop element from list
**	
**	@param	lst		pointer  to poiner to list
**	@param	key		content for search
**	@return	t_list*	pointer to element
*/
t_list	*ft_lstpop_find(t_list **lst, const char *key)
{
	t_list	*elem;
	t_list	*curr;

	elem = NULL;
	curr = *lst;
	if (curr && !ft_strncmp(curr->val, key, ft_keylen(key)))
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		return (elem);
	}
	while (curr && curr->next)
	{
		if (!ft_strncmp(curr->next->val, key, ft_keylen(key)))
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

/*
 * @brief	create new massive (like result ft_split) from list.
 * 			Starts from the last element of list!
 * 
 * @param 	pointer to lst 
 * @return 	char** new array
 */
char	**ft_lst_get_array(t_list *lst)
{
	int		size_array;
	char	**arr;

	size_array = ft_lstsize(lst) + 1;
	arr = ft_malloc_x(sizeof(*arr) * size_array);
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

/*
 * @brief	create new string from the hole list!
 * 
 * @param 	pointer to lst 
 * @return 	char*	new string
 */
char	*ft_lstdup_str(t_list *lst)
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

/*
**	@brief	adds new element to the end of the list.
**			double checks for allocation errors
**	
**	@param	lst		pointer to list
**	@param	new		pointer to new element
*/
void	ft_lst_add_end(t_list **lst, t_list *new)
{
	if (!new || !new->val)
		ft_critical_error("Now it's impossible error", NULL);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

/*
**	@brief	adds new element to end on command list
**	@param	lst		pointer to cmnd list
**	@param	new		pointer to new element
*/
void	ft_cmnd_add_end(t_cmnd **lst, t_cmnd *new)
{
	t_cmnd	*curr;

	curr = *lst;
	if (curr)
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		*lst = new;
}