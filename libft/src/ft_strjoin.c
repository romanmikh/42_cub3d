/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:28 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:28 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strjoin *********************************** */
/*   Combines two text strings, 's1' and 's2', into a single longer text.     */
/*                                                                            */
/*   In layman's terms: It's like putting two pieces of text together to make */
/*   a longer one, creating a new text. If something's missing or there isn't */
/*   enough space, it won't work and returns nothing.                         */
/* ************************************************************************** */

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*pt;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen (s2) + 1;
	if (len == 0)
		return (NULL);
	pt = (char *)malloc(sizeof(char) * len);
	if (!pt)
		return (NULL);
	result = pt;
	while (*s1)
		*pt++ = *s1++;
	while (*s2)
		*pt++ = *s2++;
	*pt = '\0';
	return (result);
}
