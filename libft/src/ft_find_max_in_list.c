/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_max_in_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:19 by rocky             #+#    #+#             */
/*   Updated: 2024/04/15 16:45:00 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_max_in_list(int a[], int size)
{
	int	max;
	int	i;

	max = INT_MIN;
	i = 0;
	while (i < size)
	{
		if (a[i] > max)
			max = a[i];
		i++;
	}
	return (max);
}
