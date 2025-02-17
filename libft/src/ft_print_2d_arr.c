/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_2d_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:37:13 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/09 19:37:16 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_2d_arr(char **arr, char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) > 0)
		ft_printf(GRN"----- 		%s[]		-----\n"RESET, name);
	while (arr && arr[i])
	{
		ft_printf(GRN"arr[%d]:	%s		at add:	%p	\n"RESET, \
			i, arr[i], arr[i]);
		i++;
	}
}
