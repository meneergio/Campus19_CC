/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:19:42 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/08 15:38:45 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*#include <stdio.h>

int	main(void)
{
	printf("=== Eenvoudige ft_isdigit tester ===\n\n");
	
	// Test cijfers 0-9 (moeten 1 retourneren)
	printf("Cijfers (moeten 1 geven):\n");
	for (char c = '0'; c <= '9'; c++)
		printf("'%c' -> %d\n", c, ft_isdigit(c));

	// Test niet-cijfers (moeten 0 retourneren)
	printf("\nNiet-cijfers (moeten 0 geven):\n");
	printf("'A' -> %d\n", ft_isdigit('A'));
	printf("'z' -> %d\n", ft_isdigit('z'));
	printf("' ' -> %d\n", ft_isdigit(' '));
	printf("'@' -> %d\n", ft_isdigit('@'));
	printf("'\\0' -> %d\n", ft_isdigit('\0'));

	return (0);
}*/
