/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:42:22 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/22 14:26:38 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
    char arr1[] = "Hello";
    char arr2[] = "Hello";
    
    // Vergelijk de eerste 5 bytes van arr1 en arr2
    int result = ft_memcmp(arr1, arr2, sizeof(arr1));
    printf("Vergelijking van arr1 en arr2: %d\n", result); 
										// Verwacht 0 omdat ze gelijk zijn

    char arr3[] = "Hello";
    char arr4[] = "World";
    
    // Vergelijk de eerste 5 bytes van arr3 en arr4
    result = ft_memcmp(arr3, arr4, sizeof(arr3));
    printf("Vergelijking van arr3 en arr4: %d\n", result); 
							// Verwacht een negatieve waarde omdat 'H' < 'W'

    return 0;
}
*/
