/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:11:12 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/10 18:27:22 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
int main(void)
{
    printf("%d\n", ft_strncmp("banaantjes", "banaan", 6)); // Moet 0 geven
    printf("%d\n", ft_strncmp("banaantjes", "banaan", 7)); // Moet positief zijn
    printf("%d\n", ft_strncmp("banaan", "banaantjes", 7)); // Moet negatief zijn
    printf("%d\n", ft_strncmp("abcd", "abcf", 3)); // Moet 0 geven 
    printf("%d\n", ft_strncmp("abcd", "abcf", 4)); // Moet negatief zijn
	return (0);
}
*/
