/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strncmp *********************************** */
/*   Compares the first 'n' characters of two text strings, 's1' and 's2,'    */
/*   returning an integer value indicating their relationship.                */
/*                                                                            */
/*   In layman's terms: It's like comparing the beginnings of two sentences   */
/*   to see if they are the same or which comes first in the dictionary. If   */
/*   something's different or 'n' is exhausted, it returns a result           */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
