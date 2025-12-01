/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:19 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 17:45:53 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	while (src[srclen])
		srclen++;
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
/*
#include <stdio.h>
int	main()
{
    char src[] = "Hello World!";  // Bronstring
    char dest[10];               // Bestemming (kleiner dan src)
    unsigned int result;

    // Kopieer met ft_strlcpy
    result = ft_strlcpy(dest, src, sizeof(dest));

    // Print resultaat
    printf("Bronstring:   \"%s\" (lengte: %zu)\n", src, sizeof(src) - 1);
    printf("Bestemming:   \"%s\"\n", dest);
    printf("Gekopieerd:   %u karakters (inclusief '\\0')\n", result);
    printf("Paste alles?  %s\n", result == sizeof(src) ? "Ja" : "Nee");

    return 0;
}*/
//Bronstring:   "Hello World!" (lengte: 12)
//Bestemming:   "Hello Wor"
//Gekopieerd:   12 karakters (inclusief '\0')
//Paste alles?  Nee
