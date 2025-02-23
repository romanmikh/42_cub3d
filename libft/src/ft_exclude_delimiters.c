/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exclude_delimiters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:02:41 by rocky             #+#    #+#             */
/*   Updated: 2024/06/14 10:02:44 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_exclude_delimiters(const char *str, char *delims)
{
	while (*str && (ft_strchr(delims, *str) != NULL))
		str++;
	return (str);
}
