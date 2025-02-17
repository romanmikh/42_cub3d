/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <rmikhayl@student.42london.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:47:43 by rocky             #+#    #+#             */
/*   Updated: 2024/01/07 15:47:43 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_int(int n)
{
	int		len;
	char	*num;

	num = ft_itoa(n);
	len = ft_print_str(num);
	free(num);
	return (len);
}
