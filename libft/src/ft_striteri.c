/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:28 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:28 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_striteri ********************************** */
/*   Applies a given function 'f' to each character of the string 's'         */
/*   along with its index. If 's' or 'f' is NULL, does nothing.               */
/*                                                                            */
/*   Difference from ft_strmapi:                                            */
/*   - This function modifies the original string 's' in-place, while        */
/*     ft_strmapi creates a new string with the modified characters and      */
/*     returns it, leaving the original 's' unchanged.                        */
/*                                                                            */
/*   In layman's terms: It's like reading a written text and performing a    */
/*   specific action on each letter while keeping track of its position.      */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
