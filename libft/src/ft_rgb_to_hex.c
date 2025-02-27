/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:25:23 by rocky             #+#    #+#             */
/*   Updated: 2025/02/27 11:25:27 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_rgb_to_hex(int *rgb_int_arr)
{
	unsigned long	rgb_hex;
	int				r;
	int				g;
	int				b;

	r = rgb_int_arr[0];
	g = rgb_int_arr[1];
	b = rgb_int_arr[2];
	rgb_hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (rgb_hex);
}
