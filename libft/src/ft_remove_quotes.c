/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:12:43 by rocky             #+#    #+#             */
/*   Updated: 2024/09/26 18:12:45 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_quotes(char *str, char quote_type)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = NULL;
	if (len > 1 && str[0] == quote_type && str[len - 1] == quote_type)
	{
		new_str = ft_strndup(str + 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str));
}
