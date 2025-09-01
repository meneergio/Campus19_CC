/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:53:43 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 15:01:30 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	reverse_copy(unsigned char *dest,
							const unsigned char *src, size_t len)
{
	size_t	i;

	i = len;
	while (i > 0)
	{
		dest[i - 1] = src[i - 1];
		i--;
	}
}

static void	forward_copy(unsigned char *dest,
							const unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (dest > source)
		reverse_copy(dest, source, len);
	else
		forward_copy(dest, source, len);
	return (dst);
}
/*
// als dest > source, dan kopieren we achterwaarts om de originele data
// niet voortijdig te overschrijven, anders gewoon voorwaarts
// "static" omdat de functies reverse_copy en forward_copy niet
// per ongeluk in andere bestanden zouden aangeroepen worden, alleen hier
#include <stdio.h>
#include <string.h> // voor vergelijking met standaard memmove
#include "libft.h"  // mijn versie van ft_memmove

int main(void)
{
    char buffer1[20] = "Hello, world!";
    char buffer2[20] = "Hello, world!";

    printf("=== ft_memmove testen ===\n\n");

    // Voorbeeld 1: normale kopie
    printf("Origineel: %s\n", buffer1);
    ft_memmove(buffer1 + 7, buffer1, 5); // kopieer "Hello" naar positie 7
    printf("Na ft_memmove (overlap): %s\n", buffer1);

    // Voorbeeld 2: overlappende geheugenblokken (achterwaarts)
    printf("\nOrigineel (standaard memmove): %s\n", buffer2);
    memmove(buffer2 + 7, buffer2, 5); // standaard C-functie
    printf("Na standaard memmove: %s\n", buffer2);

    // Voorbeeld 3: geen overlap
    char src[] = "12345";
    char dest[10] = "abcde";

    printf("\nVoorbeeld zonder overlap:\n");
    printf("Voor: dest = %s\n", dest);
    ft_memmove(dest, src, 5);
    printf("Na ft_memmove: dest = %s\n", dest);

    return 0;
}
*/
