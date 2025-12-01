/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:27:30 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 17:46:22 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && (dst_len + i) < (dstsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
//    Als dstsize kleiner is dan of gelijk aan de lengte van dst, 
//		retourneer dan gewoon dstsize + src_len (zoals de originele strlcat)

//    Kopieer alleen zoveel karakters van src naar dst als er ruimte is,
//     met 1 karakter over voor de null-terminator

//    Zorg altijd voor een null-terminator aan het einde	
	
#include <stdio.h>

void	test_strlcat(char *dst, const char *src,
					 size_t size, size_t expected_len)
{
	size_t	result;
	char	buffer[100]; // Grote buffer voor tests

	// Maak een kopie van dst om te modificeren
	ft_strlcpy(buffer, dst, sizeof(buffer));
	
	printf("\nTest: \"%s\" + \"%s\" (buffer size: %zu)\n", dst, src, size);
	result = ft_strlcat(buffer, src, size);
	printf("Resultaat: \"%s\" (lengte: %zu)\n", buffer, result);
	printf("Verwacht:  lengte = %zu\n", expected_len);
}

int	main(void)
{
	char	dst1[20] = "Hello";
	char	dst2[10] = "Hi";
	char	dst3[5] = "Test";
	char	dst4[3] = "A";

	// Normale gevallen
	test_strlcat(dst1, " world!", 20, 12);  // Past volledig
	test_strlcat(dst2, " everyone", 10, 11); // Past gedeeltelijk
	test_strlcat(dst3, "123", 5, 7);        // Buffer te klein
	test_strlcat(dst4, "BC", 3, 3);         // Geen ruimte voor '\0'

	// Edge cases
	test_strlcat("", "42", 5, 2);           // Lege dst
	test_strlcat("Hello", "", 10, 5);        // Lege src
	test_strlcat("A", "B", 1, 2);            // Geen ruimte
	test_strlcat("A", "B", 0, 2);            // dstsize = 0

	return (0);
}
*/
//results
//"Hello world!"       (lengte: 12)
//"Hi everyo"          (lengte: 11)
//"Test"               (lengte: 7)
//"AB"                 (lengte: 3)
//"42"                 (lengte: 2)
//"Hello"              (lengte: 5)
//"A"                  (lengte: 2)
//"A"                  (lengte: 2)
