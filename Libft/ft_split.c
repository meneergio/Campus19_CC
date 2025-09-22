/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:53:01 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/18 16:01:30 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	return (word);
}

static void	free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		result[i] = get_word(s, c);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		s += ft_strlen(result[i]);
		i++;
	}
	return (result);
}
/*
// test
#include "libft.h"
#include <stdio.h>

void	print_split(char **arr)
{
	if (!arr)
	{
		printf("(NULL)\n");
		return;
	}
	while (*arr)
	{
		printf("[%s] ", *arr);
		arr++;
	}
	printf("\n");
}

int	main(void)
{
	char	**result;

	printf("=== Testing ft_split ===\n\n");

	// Test 1: Normaal geval
	result = ft_split("Hello,world,42", ',');
	printf("Test1: ");
	print_split(result);
	free(result);

	// Test 2: Lege string
	result = ft_split("", ',');
	printf("Test2: ");
	print_split(result);
	free(result);

	// Test 3: Alleen delimiters
	result = ft_split(",,,,", ',');
	printf("Test3: ");
	print_split(result);
	free(result);

	// Test 4: NULL input
	result = ft_split(NULL, ',');
	printf("Test4: ");
	print_split(result);

	return (0);
}
// return
//=== Testing ft_split ===
//
//Test1: [Hello] [world] [42] 
//Test2: 
//Test3: 
//Test4: (NULL)
*/
