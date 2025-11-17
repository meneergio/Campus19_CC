/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:10:44 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/22 15:51:16 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			len_s;
	char			*substr;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	if (len > len_s - start)
		len = len_s - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		substr[i] = s[start];
		++start;
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

/*
	The function ft_substr extracts a substring from the given string by
	allocating sufficient memory for the new string starting at index start
	and ending at len characters.

	RETURN VALUE :
	A pointer to the new string.
	NULL if the memory allocation fails.
*/
/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *str = "Hello, world!";
	char *sub;

	// Normaal geval
	sub = ft_substr(str, 7, 5);  // "world"
	printf("Test 1: %s\n", sub);
	free(sub);

	// Len > stringlengte vanaf start
	sub = ft_substr(str, 7, 50);  // "world!"
	printf("Test 2: %s\n", sub);
	free(sub);

	// start == strlen → lege string
	sub = ft_substr(str, ft_strlen(str), 5);  // ""
	printf("Test 3: '%s'\n", sub);
	free(sub);

	// start > strlen → lege string
	sub = ft_substr(str, 100, 5);  // ""
	printf("Test 4: '%s'\n", sub);
	free(sub);

	// len = 0
	sub = ft_substr(str, 5, 0);  // ""
	printf("Test 5: '%s'\n", sub);
	free(sub);

	//  NULL string
	sub = ft_substr(NULL, 0, 5);  // NULL
	printf("Test 6: %s\n", sub == NULL ? "NULL" : sub);
	// geen free nodig want sub == NULL

	return 0;
}*/
