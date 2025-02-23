/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strlcpy *********************************** */
/*   Copies text from 'src' to 'dst' ensuring it fits within 'size'           */
/*   characters. Returns the length of the copied text. If something's        */
/*   missing or 'size' is too small, it won't work as intended.               */
/*                                                                            */
/*   In layman's terms: It's like copying a passage from one page to another, */
/*   making sure it fits without cutting off any words. If there's not enough */
/*   space or some content is missing, it won't be a perfect copy.            */
/* ************************************************************************** */

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = dst;
	s = src;
	n = size;
	if (n > 0)
	{
		while (--n > 0 && *s != '\0')
			*d++ = *s++;
		*d = '\0';
	}
	while (*s != '\0')
		s++;
	return (s - src);
}
