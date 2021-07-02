#include "libft.h"

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
