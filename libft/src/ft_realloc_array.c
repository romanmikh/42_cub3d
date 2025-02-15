/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:19:46 by rocky             #+#    #+#             */
/*   Updated: 2024/09/26 19:19:50 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_array(char **array, int old_size, int new_size)
{
	char	**new_array;
	int		i;

	new_array = malloc(sizeof(char *) * (new_size + 1));
	if (!new_array)
		exit(1);
	i = 0;
	while (i < old_size)
	{
		new_array[i] = array[i];
		i++;
	}
	while (i < new_size)
	{
		new_array[i] = NULL;
		i++;
	}
	free(array);
	return (new_array);
}
