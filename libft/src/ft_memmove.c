/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_memmove *********************************** */
/*   Moves 'n' bytes from 'src' to 'dest' without overlap and returns 'dest'. */
/*   The original 'src' memory remains unchanged.                             */
/*                                                                            */
/*   In layman's terms: It safely shifts a block of data from one place to    */
/*   another without causing any issues or conflicts and gives you the        */
/*   destination.                                                             */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*d;
	const char		*s;

	d = dest;
	s = src;
	if (d == s)
		return (dest);
	if (d < s || d >= s + n)
		ft_memcpy(d, s, n);
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}
