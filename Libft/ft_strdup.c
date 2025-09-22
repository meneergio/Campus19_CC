/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:52:53 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 11:59:42 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char		*dest;
	size_t		len;

	len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, len + 1);
	return (dest);
}
/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *s1 = "Hello 42";
    char *s2 = "";
    char *s3 = NULL;
    char *dup;

    // Test 1: Normale string
    dup = ft_strdup(s1);
    printf("Test1: \"%s\"\n", dup);
    free(dup);

    // Test 2: Lege string
    dup = ft_strdup(s2);
    printf("Test2: \"%s\"\n", dup);
    free(dup);

    // Test 3: NULL-input
    dup = ft_strdup(s3);
    printf("Test3: %s\n", dup ? "FAIL" : "OK (NULL returned)");

    return (0);
}
*/
/*
#include <stdio.h>

int main()
{
    char *copy = ft_strdup("roekiefroekie");

    printf("Origineel: %s\n", "roekiefroekie");
    printf("Kopie: %s\n", copy);

    free(copy);

    return (0);
}*/
