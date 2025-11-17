/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:10:18 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/10 13:22:25 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*array;
	size_t				i;

	array = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (array[i] == (unsigned char)c)
			return ((void *)&array[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
    const char str[] = "Hello, 42!";
    int c = '4';  // Het karakter waar we naar zoeken
    size_t n = 10; // Aantal bytes om te doorzoeken

    // Test met een gevonden karakter
    char *result = ft_memchr(str, c, n);
    if (result != NULL)
        printf("Gevonden '%c' op positie: %ld\n", c, result - str);
    else
        printf("Karakter '%c' niet gevonden\n", c);

    // Test met een niet-gevonden karakter
    c = 'z';  // Een karakter dat niet in de string voorkomt
    result = ft_memchr(str, c, n);
    if (result != NULL)
        printf("Gevonden '%c' op positie: %ld\n", c, result - str);
    else
        printf("Karakter '%c' niet gevonden\n", c);

    return 0;
}
// verwachte return
// Gevonden '4' op positie: 7
// Karakter 'z' niet gevonden
*/
