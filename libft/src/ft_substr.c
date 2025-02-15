/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_substr ************************************ */
/*   Extracts a substring from 's' starting at the specified 'start'          */
/*   position and up to 'len' characters. Returns a new string with the       */
/*   extracted content or NULL if memory allocation fails or 'start' is       */
/*   out of bounds.                                                           */
/*                                                                            */
/*   In layman's terms: It's like cutting a portion of a sentence from a      */
/*   specific point and up to a certain length to create a new shorter        */
/*   sentence. If something goes wrong or 'start' is too far away, you get    */
/*   nothing.                                                                 */
/* ************************************************************************** */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	size;

	size = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		size = 0;
	else if (size > len)
		size = len;
	new_str = (char *)malloc(size + 1);
	if (!s || !new_str)
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}
