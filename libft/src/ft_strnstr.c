/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strnstr *********************************** */
/*   Searches for the first occurrence of 'little' within 'big,' up to 'n'    */
/*   characters. Returns a pointer to the found substring or NULL if not      */
/*   found.                                                                   */
/*                                                                            */
/*   In layman's terms: It's like looking for a specific word or phrase in a  */
/*   longer text, but you can only search within the first 'n' characters. If */
/*   it's there, you get a pointer to it; otherwise, you get nothing.         */
/* ************************************************************************** */

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	little_len;

	if (!big && n == 0)
		return (NULL);
	little_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (*big != '\0' && n >= little_len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		n--;
	}
	return (NULL);
}
