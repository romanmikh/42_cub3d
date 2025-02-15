/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:05 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/05/15 14:50:06 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_double(const char *n)
{
	unsigned long	i;
	int				p;

	i = 0;
	while (n[i] && (n[i] == '\t' || n[i] == '\n' || n[i] == '\v'
			|| n[i] == '\f' || n[i] == '\r' || n[i] == ' '))
		i++;
	if (n[i] && (n[i] == '+' || n[i] == '-'))
		i++;
	if (!n[i])
		return (FALSE);
	p = FALSE;
	while (n[i])
	{
		if (!ft_isdigit(n[i]) && n[i] != '.' && n[i] != ',')
			return (FALSE);
		if ((n[i] == '.' || n[i] == ',') && p == TRUE)
			return (FALSE);
		if (n[i] == '.' || n[i] == ',')
			p = TRUE;
		i++;
	}
	return (TRUE);
}
