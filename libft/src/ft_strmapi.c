/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strmapi *********************************** */
/*   Applies a given function 'f' to each character of the string 's' along   */
/*   with its index. Returns a new string with the modified characters.       */
/*   If 's' or 'f' is NULL or memory allocation fails, returns NULL.          */
/*                                                                            */
/*   Difference from ft_striteri:                                             */
/*   - This function creates a new string with the modified characters and    */
/*     returns it, while ft_striteri modifies the original string in-place.   */
/*                                                                            */
/*   In layman's terms: It's like reading a text and making changes to each   */
/*   letter while remembering where each letter was originally located.       */
/* ************************************************************************** */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}
