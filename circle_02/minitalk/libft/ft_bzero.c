/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:26:44 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/10 11:41:17 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>
#include <strings.h> // Voor de standaard bzero ter vergelijking

void	print_memory(void *s, size_t n)
{
    unsigned char *p = s;
    for (size_t i = 0; i < n; i++)
        printf("%02x ", p[i]);
    printf("\n");
}

int	main(void)
{
    char buffer1[10] = "abcdefghi";
    char buffer2[10] = "abcdefghi";
    int numbers[3] = {1, 2, 3};
    
    printf("=== Test 1: Volledige string nulzetten ===\n");
    printf("Origineel: \"%s\" -> ", buffer1);
    print_memory(buffer1, 10);
    
    ft_bzero(buffer1, 10);
    bzero(buffer2, 10);
    
    printf("ft_bzero: ");
    print_memory(buffer1, 10);
    printf("bzero:    ");
    print_memory(buffer2, 10);
    
    printf("\n=== Test 2: Gedeeltelijk nulzetten ===\n");
    ft_bzero(buffer1, 3);
    printf("Eerste 3 bytes nul: ");
    print_memory(buffer1, 10);
    
    printf("\n=== Test 3: Integer array nulzetten ===\n");
    printf("Origineel: ");
    print_memory(numbers, sizeof(numbers));
    ft_bzero(numbers, sizeof(numbers));
    printf("Na bzero: ");
    print_memory(numbers, sizeof(numbers));
    
    printf("\n=== Test 4: Edge case - n = 0 ===\n");
    char test = 'X';
    ft_bzero(&test, 0);
    printf("Karakter blijft '%c' (ongewijzigd)\n", test);
    
    return (0);
}
*/
