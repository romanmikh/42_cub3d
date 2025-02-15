#include "libft.h"

/*
	DESCRIPTION :
	The function ft_lstdelone deletes the content of a list node with the
	function passed as parameter before freeing the memory of the node.

	RETURN VALUE :
	None.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		(del)(lst->content);
	free(lst);
}
