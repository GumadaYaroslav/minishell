#include "minishell.h"

size_t	ft_keylen(const char *keyval)
{
	size_t	i;

	i = 0;
	while(keyval[i] && keyval[i] != '=')
		i++;
	return (i);
}

char	*get_val_from_keyval(const char *keyval)
{
	size_t	i;

	if (!keyval)
		return (ft_strdup(""));
	i = ft_keylen(keyval);
	if (i && keyval[i] == '=')
		return (ft_strdup(keyval + i + 1));
	else
		return (ft_strdup(""));
}


/*
**	@brief	allocates memory and copy the char to new string
**	
**	@param	s1		char
**	@return	char*	pointer to new string or NULL
*/
char	*ft_chrdup(const char ch)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(*new_str) * 2);
	if (!new_str)
		return (new_str);
	new_str[0] = ch;
	new_str[1] = 0;
	return (new_str);
}
