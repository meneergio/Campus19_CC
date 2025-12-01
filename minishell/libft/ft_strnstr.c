/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:32:14 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/09 17:04:41 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(needle[i]))
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && (i + j) < len
			&& haystack[i + j] == needle [j])
		{
			j++;
		}
		if (!(needle[j]))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*str = "Hello 42 Paris!";
	const char	*empty = "";
	size_t		len = 15;

	printf("=== Testing ft_strnstr ===\n\n");
	printf("Haystack: \"%s\" (len: %zu)\n", str, len);
	
	// Basic tests
	printf("ft_strnstr(\"42\") = %s\n", ft_strnstr(str, "42", len));      
// "42 Paris!"
	printf("ft_strnstr(\"Paris\") = %s\n", ft_strnstr(str, "Paris", len)); 
// "Paris!"
	printf("ft_strnstr(\"Hello\") = %s\n", ft_strnstr(str, "Hello", len)); 
// "Hello 42 Paris!"
	printf("ft_strnstr(\"42\") with len=5: %s\n", ft_strnstr(str, "42", 5)); 
// NULL
	
	// Edge cases
	printf("ft_strnstr(empty) = %s\n", ft_strnstr(str, empty, len));      
// "Hello 42 Paris!"
	printf("ft_strnstr(\"not\") = %s\n", ft_strnstr(str, "not", len));    
// NULL
	printf("ft_strnstr(\"!\") = %s\n", ft_strnstr(str, "!", len));        
// "!"
	printf("ft_strnstr(\"Paris\") with len=12: %s\n", 
			ft_strnstr(str, "Paris", 12)); // NULL

	return (0);
}
*/
