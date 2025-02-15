#include "libft.h"
/*
	DESCRIPTION :
	The function ft_ishexdigit checks whether c is a hexadecimal
	digit character or not.

	RETURN VALUE:
	Non-zero if c is a hexadecimal digit, zero if not.
*/
int	ft_ishexdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	c = ft_toupper(c);
	if (c >= 'A' && c <= 'F')
		return (c);
	else
		return (0);
}
