/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:27 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:27 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_putstr_fd ********************************* */
/*   Writes the string 's' to the specified file descriptor 'fd'.             */
/*   A file descriptor is a numeric identifier for an I/O resource.           */
/* ************************************************************************** */

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
