/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:19:30 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/09 17:06:33 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char str[] = "Hello, world!";
	int ch1 = 'o';
	int ch2 = 'l';
	int ch3 = 'z';
	int ch4 = '\0';

	printf("=== Testing ft_strrchr ===\n\n");
	printf("String: \"%s\"\n\n", str);

	// Normale gevallen
	printf("ft_strrchr('%c') = %s\n", ch1, ft_strrchr(str, ch1));  // "orld!"
	printf("ft_strrchr('%c') = %s\n", ch2, ft_strrchr(str, ch2));  // "ld!"
	printf("ft_strrchr('%c') = %s\n", ch3, ft_strrchr(str, ch3));  // (null)
	printf("ft_strrchr('\\0') = \"%s\"\n", ft_strrchr(str, ch4));  
// "" (lege string)

	// Edge case: lege string
	const char empty[] = "";
	printf("ft_strrchr in empty string = %s\n", ft_strrchr(empty, 'a')); 
// (null)

	return (0);
}
*/
