/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:27:54 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/14 13:32:06 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
/*
// is zoals putstr_fd naar voegt een newline toe

int	main(void)
{
	ft_putendl_fd("Hello, world!", 1); // Schrijf naar stdout (terminal)
	ft_putendl_fd("Dit is stderr!", 2); // Schrijf naar stderr (foutkanaal)
	return (0);
}
*/
