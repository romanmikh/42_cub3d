/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <rmikhayl@student.42london.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:47:43 by rocky             #+#    #+#             */
/*   Updated: 2024/01/07 15:47:43 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formatssssss(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_print_int(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_unsigned_dec(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_unsigned_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		len += ft_print_percent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formatssssss(args, str[i + 1]);
			i++;
		}
		else
			len += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
