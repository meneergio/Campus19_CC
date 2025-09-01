/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:29:52 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/13 16:25:09 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	const char		*s;

	if (!dst && !src)
		return (NULL);
	i = 0;
	d = dst;
	s = src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

void	print_memory(const void *addr, size_t size)
{
	const unsigned char *p = addr;
	
	for (size_t i = 0; i < size; i++)
		printf("%02x ", p[i]);
	printf("\n");
}

int	main(void)
{
	char	src1[] = "Hello 42!";
	char	dst1[20];
	char	dst2[20];
	int		src2[] = {1, 2, 3, 4, 5};
	int		dst3[5];
	size_t	n;

	// Test 1: Normal string copy
	n = ft_strlen(src1) + 1;
	ft_memcpy(dst1, src1, n);
	memcpy(dst2, src1, n);
	printf("=== Test 1: String copy ===\n");
	printf("ft_memcpy: \"%s\"\n", dst1);
	printf("memcpy:    \"%s\"\n", dst2);

	// Test 2: Partial copy
	n = 5;
	ft_memcpy(dst1, src1, n);
	printf("\n=== Test 2: Partial copy (5 bytes) ===\n");
	printf("Result: \"%.*s\"\n", (int)n, dst1);
	print_memory(dst1, n);

	// Test 3: Integer array copy
	n = sizeof(src2);
	ft_memcpy(dst3, src2, n);
	printf("\n=== Test 3: Integer array copy ===\n");
	print_memory(dst3, sizeof(dst3));

	// Test 4: Edge case - NULL pointers
	printf("\n=== Test 4: NULL pointers ===\n");
	printf("Return value: %p\n", ft_memcpy(NULL, NULL, 5));

	return (0);
}*/
/*
results
=== Test 1: String copy ===
ft_memcpy: "Hello 42!"
memcpy:    "Hello 42!"

=== Test 2: Partial copy (5 bytes) ===
Result: "Hello"
48 65 6c 6c 6f 

=== Test 3: Integer array copy ===
01 00 00 00 02 00 00 00 03 00 00 00 04 00 00 00 05 00 00 00 

=== Test 4: NULL pointers ===
Return value: (nil)
*/
