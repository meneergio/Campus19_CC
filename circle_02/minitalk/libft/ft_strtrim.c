/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:25:50 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/13 17:30:14 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed_str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + start, len + 1);
	return (trimmed_str);
}
/*
#include <stdio.h>

int main(void)
{
    char *s1 = "   Hello, World!   ";
    char *set = " ";
    char *result;

    result = ft_strtrim(s1, set);
    if (result)
    {
        printf("Origineel: '%s'\n", s1);
        printf("Getrimd: '%s'\n", result);
        free(result);  
		// Vergeet niet om het gealloceerde geheugen vrij te geven!
    }
    else
    {
        printf("Er is een fout opgetreden bij het trimmen van de string.\n");
    }

    return 0;
}
*/
