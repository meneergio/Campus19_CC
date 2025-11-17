/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:30:29 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/22 14:59:04 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int main(void)
{
    char *str1 = "Hello, ";
    char *str2 = "world!";
    char *result;

    result = ft_strjoin(str1, str2);
    if (result)
    {
        printf("Test 1: %s\n", result);  // Verwacht: "Hello, world!"
        free(result);  // Vergeet niet het geheugen vrij te geven!
    }

    result = ft_strjoin("42", " students");
    if (result)
    {
        printf("Test 2: %s\n", result);  // Verwacht: "42 students"
        free(result);
    }

    return 0;
}
*/
