/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr._fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:31 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/14 13:20:19 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
/*
// schrijft een string naar een file descriptor
// 1 is standaard output, 2 is foutmelding
#include "libft.h"

int	main(void)
{
	ft_putstr_fd("Hello, world!\n", 1);
	ft_putstr_fd("Dit is stderr!\n", 2);
	return (0);
}
*/
