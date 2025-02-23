/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/06/05 17:16:45 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strcat ************************************ */
/*   Combines two text strings, 'dst' and 'src', ensuring the result fits     */
/*   within 'size' characters. Returns the length of the combined text. If    */
/*   something's missing or 'size' is too small, undefined behavoiur.         */
/*                                                                            */
/*   In layman's terms: It's like adding more words to an existing sentence,  */
/*   making sure it doesn't get too long. If there's not enough space or      */
/*   something is missing, it doesn't work right and doesn't give you the     */
/*   correct result.                                                          */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
