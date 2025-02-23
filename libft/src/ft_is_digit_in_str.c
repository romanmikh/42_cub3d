/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit_in_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:58:50 by rocky             #+#    #+#             */
/*   Updated: 2025/02/23 13:58:52 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_digit_in_str(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (str[i])
	{
		if (ft_is_digit(str[i]) == 1)
			flag = true;
		i++;
	}
	return (flag);
}
