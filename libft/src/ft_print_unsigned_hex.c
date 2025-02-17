/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_hex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <rmikhayl@student.42london.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:47:43 by rocky             #+#    #+#             */
/*   Updated: 2024/01/07 15:47:43 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

void	ft_put_hex(unsigned int n, const char upper_lower)
{
	if (n >= 16)
	{
		ft_put_hex(n / 16, upper_lower);
		ft_put_hex(n % 16, upper_lower);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
		{
			if (upper_lower == 'x')
				ft_putchar_fd((n - 10 + 'a'), 1);
			if (upper_lower == 'X')
				ft_putchar_fd((n - 10 + 'A'), 1);
		}
	}
}

int	ft_print_unsigned_hex(unsigned int n, const char upper_lower)
{
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
		ft_put_hex(n, upper_lower);
	return (ft_hex_len(n));
}
