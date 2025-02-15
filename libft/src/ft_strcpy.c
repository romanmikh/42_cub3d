/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 17:17:04 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strlcpy *********************************** */
/*   Copies text from 'src' to 'dst' ensuring it fits within 'size'           */
/*   characters. Returns the length of the copied text. If something's        */
/*   missing or 'size' is too small, it won't work as intended.               */
/*                                                                            */
/*   In layman's terms: It's like copying a passage from one page to another, */
/*   making sure it fits without cutting off any words. If there's not enough */
/*   space or some content is missing, it won't be a perfect copy.            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}
