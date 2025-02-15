/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:49:25 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/05/15 14:49:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_num(const char *n)
{
	unsigned long	i;

	i = 0;
	while (n[i] && (n[i] == '\t' || n[i] == '\n' || n[i] == '\v'
			|| n[i] == '\f' || n[i] == '\r' || n[i] == ' '))
		i++;
	if (n[i] && (n[i] == '+' || n[i] == '-'))
		i++;
	if (!n[i])
		return (FALSE);
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
