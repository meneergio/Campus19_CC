/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:46:18 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/08 15:18:25 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*
#include <stdio.h>

int main(void)
{
    printf("ft_isalpha('A') = %d\n", ft_isalpha('A'));  // Moet 1 geven
    printf("ft_isalpha('z') = %d\n", ft_isalpha('z'));  // Moet 1 geven
    printf("ft_isalpha('4') = %d\n", ft_isalpha('4'));  // Moet 0 geven
    printf("ft_isalpha('@') = %d\n", ft_isalpha('@'));  // Moet 0 geven
    return (0);
}
*/
