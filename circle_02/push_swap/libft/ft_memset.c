/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:55:46 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/09 18:07:00 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (b);
}
/*
#include <stdio.h>

int main(void)
{
    char str[20] = "Hello, world!";

    printf("Before memset: %s\n", str);

    // Vul de eerste 5 bytes van `str` met 'X'
    ft_memset(str, 'X', 5);

    printf("After memset: %s\n", str);

    return 0;
}
*/
