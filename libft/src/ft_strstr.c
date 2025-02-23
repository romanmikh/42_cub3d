/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strstr ************************************ */
/*   Searches for the first occurrence of 'little' within 'big,'.             */
/*   Returns a pointer to the found substring or NULL if not found.           */
/*                                                                            */
/*                                                                            */
/*   In layman's terms: It's like looking for a specific word or phrase in a  */
/*   longer text. If it's there, you get a pointer to it, otherwise NULL.     */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	size_t	little_len;

	if (!big)
		return (NULL);
	little_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (*big != '\0')
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
