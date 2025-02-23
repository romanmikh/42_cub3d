/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:28 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:28 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_strdup ************************************ */
/*   Duplicates the string 's' and returns a new identical string.            */
/*   If 's' is NULL or memory allocation fails, returns NULL.                 */
/*                                                                            */
/*   In layman's terms: It's like making a photocopy of a piece of text, so   */
/*   you have an exact copy of it to use or store separately.                 */
/* ************************************************************************** */

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*new;

	n = ft_strlen(s);
	if (!s)
		return (NULL);
	new = malloc((n + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s, n + 1);
	return (new);
}
