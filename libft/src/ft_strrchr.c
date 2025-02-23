/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:25 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:25 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strrchr *********************************** */
/*   Searches for the last occurrence of 'c' in the string 's.'               */
/*   Returns a pointer to the found character or NULL if not found.           */
/*                                                                            */
/*   In layman's terms: It's like finding the very last occurrence of a       */
/*   specific character in a sentence. If it's there, you get a pointer to it */
/*   otherwise, you get nothing.                                              */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	const char		*last_occurrence;

	last_occurrence = NULL;
	uc = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == uc)
			last_occurrence = s;
		s++;
	}
	if (*s == uc)
		return ((char *)s);
	return ((char *)last_occurrence);
}
