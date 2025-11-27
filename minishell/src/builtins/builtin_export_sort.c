/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:49:38 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/27 15:56:35 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Case-insensitive string compare (zoals bash doet)
static int	env_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	c1;
	int	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	c1 = s1[i];
	c2 = s2[i];
	if (c1 >= 'A' && c1 <= 'Z')
		c1 += 32;
	if (c2 >= 'A' && c2 <= 'Z')
		c2 += 32;
	return (c1 - c2);
}

// Sorteer de array alfabetisch (bubble sort)
void	export_sort_env_array(t_env_entry **arr, int count)
{
	int			i;
	int			j;
	t_env_entry	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (env_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

// Print de gesorteerde env-entries
void	export_print_sorted_env(t_env_entry **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
		i++;
	}
}

// Tel het aantal entries in de env-lijst
int	export_count_env_entries(t_env_entry *env)
{
	int			count;
	t_env_entry	*p;

	count = 0;
	p = env;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}

// Bouw een array van pointers naar env-entries
t_env_entry	**export_build_env_array(t_env_entry *env, int count)
{
	t_env_entry	**arr;
	t_env_entry	*p;
	int			i;

	arr = malloc(sizeof(t_env_entry *) * count);
	if (!arr)
		return (NULL);
	p = env;
	i = 0;
	while (p)
	{
		arr[i] = p;
		p = p->next;
		i++;
	}
	return (arr);
}
