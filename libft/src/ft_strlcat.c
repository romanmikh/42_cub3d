/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strlcat *********************************** */
/*   Combines two text strings, 'dst' and 'src', ensuring the result fits     */
/*   within 'size' characters. Returns the length of the combined text. If    */
/*   something's missing or 'size' is too small, undefined behavoiur.         */
/*                                                                            */
/*   In layman's terms: It's like adding more words to an existing sentence,  */
/*   making sure it doesn't get too long. If there's not enough space or      */
/*   something is missing, it doesn't work right and doesn't give you the     */
/*   correct result.                                                          */
/* ************************************************************************** */

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		len_dst;
	size_t		remaining_space;

	len_dst = 0;
	s = src;
	d = dst;
	while (size > 0 && *d != '\0')
	{
		d++;
		size--;
		len_dst++;
	}
	remaining_space = size;
	if (remaining_space == 0)
		return (len_dst + ft_strlen(src));
	while (--remaining_space > 0 && *s != '\0')
		*d++ = *s++;
	*d = '\0';
	return (len_dst + ft_strlen(src));
}
