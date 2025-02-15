/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:28 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:28 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_memchr ************************************ */
/*   Searches for the first occurrence of a specific byte in a memory block.  */
/*   Returns a pointer to the found byte if present; otherwise, returns NULL. */
/*                                                                            */
/*   Parameters:                                                              */
/*   - 's': A pointer to the memory block to search in.                       */
/*   - 'c': The byte value to search for.                                     */
/*   - 'n': The number of bytes to search within the memory block 's'.        */
/*                                                                            */
/*   In layman's terms: It's like looking for a particular symbol or letter   */
/*   in a collection of characters. If it's found, you get a clue; otherwise, */
/*   you get nothing.                                                         */
/* ************************************************************************** */

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*st;
	unsigned char		ct;

	st = s;
	ct = (unsigned char)c;
	while (n--)
	{
		if (*st == ct)
			return ((void *)st);
		st++;
	}
	return (NULL);
}
