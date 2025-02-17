/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_repeat_check_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:36:13 by rocky             #+#    #+#             */
/*   Updated: 2024/04/15 16:41:53 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_repeat_check_int(int a[], int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (a[i] == a[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
