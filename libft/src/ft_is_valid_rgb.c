#include "libft.h"

int	ft_is_valid_rgb(int rgb)
{
	if (rgb < 0 || rgb > 255)
		return (FAILURE);
	return (SUCCESS);
}
