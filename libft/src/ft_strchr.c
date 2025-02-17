/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strchr ************************************ */
/*   Searches for the first occurrence of the character 'c' in the string     */
/*   's'. Returns a pointer to the first match if found; otherwise, returns   */
/*   NULL.                                                                    */
/*                                                                            */
/*   In layman's terms: It's like finding a specific letter or symbol in a    */
/*   written text. If the letter is there, it tells you where to look; if not,*/
/*   it says there's nothing to find.                                         */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s != '\0' && *s != uc)
		s++;
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
