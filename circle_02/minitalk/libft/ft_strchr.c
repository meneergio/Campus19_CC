/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:31:56 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 17:21:56 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	str[] = "Hello 42!";
	int		ch1 = 'l';
	int		ch2 = '4';
	int		ch3 = 'z';
	int		ch4 = '\0';

	printf("=== Testing ft_strchr ===\n\n");
	printf("Original string: \"%s\"\n", str);
	
	printf("ft_strchr('%c') = %s\n", ch1, ft_strchr(str, ch1));  // "llo 42!"
	printf("ft_strchr('%c') = %s\n", ch2, ft_strchr(str, ch2));  // "42!"
	printf("ft_strchr('%c') = %s\n", ch3, ft_strchr(str, ch3));  // (null)
	printf("ft_strchr('\\0') = %s\n", ft_strchr(str, ch4));      
												// "" (empty string after \0)

	// Edge case: searching in empty string
	printf("ft_strchr in empty string: %s\n", ft_strchr("", 'a')); // (null)

	return (0);
}
*/
