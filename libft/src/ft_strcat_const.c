/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_const.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:15:55 by rocky             #+#    #+#             */
/*   Updated: 2024/09/06 12:15:59 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_const(const char *dest, const char *src)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (dest[i] != '\0')
	{
		result[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		result[i + j] = src[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
