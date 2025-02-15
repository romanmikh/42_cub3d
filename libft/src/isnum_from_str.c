/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isnum_from_str.c                                   :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+    */
/*   By: rmikhayl <rmikhayl@student.42london.ac.uk>  +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/04/15 16:46:47 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isnum_from_str(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
	{
		str++;
		if (*str == '\0')
			return (0);
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
