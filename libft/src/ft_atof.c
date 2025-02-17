/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:17 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/05/15 14:50:18 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	res;
	double	neg;
	double	divider;
	size_t	i;

	divider = 0.1;
	res = 0;
	neg = 1;
	i = -1;
	while (str[i] < '0' || str[i] > '9')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - 48;
	}
	if (str[i] == '.' || str[i] == ',')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res + (str[i] - 48) * divider;
		divider /= 10;
		i++;
	}
	return (res * neg);
}
