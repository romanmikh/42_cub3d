#include "libft.h"

/*
	DESCRIPTION :
	The function ft_lstsize measures the size of a given list by counting
	the number of nodes in it.

	RETURN VALUE :
	The integer number of nodes in the given list.
*/

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
