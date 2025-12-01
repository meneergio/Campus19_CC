/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:48:28 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/10 21:17:41 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// verwijder één sleutel uit de env-lijst
static void	unset_one_key(const char *key, t_env_entry **env)
{
	t_env_entry	*prev;
	t_env_entry	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

// builtin unset
int	builtin_unset(char **argv, t_env_entry **env)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		unset_one_key(argv[i], env);
		i++;
	}
	return (0);
}
