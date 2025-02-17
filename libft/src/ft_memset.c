/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:28 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:28 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_memset ************************************ */
/*   Fills the first 'n' bytes of memory at 's' with the byte value 'c'.      */
/*   The original memory at 's' remains unchanged.                            */
/*                                                                            */
/*   Parameters:                                                              */
/*   - 's': A pointer to the memory to fill.                                  */
/*   - 'c': The byte value used for filling.                                  */
/*   - 'n': The number of bytes to fill at 's'.                               */
/*                                                                            */
/*   In layman's terms: It's like painting a specific area in memory with a   */
/*   particular color, ensuring that the rest of the memory is untouched.     */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = (unsigned char)c;
	return (s);
}
