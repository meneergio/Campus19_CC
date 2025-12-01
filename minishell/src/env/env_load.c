/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:17:52 by dzotti            #+#    #+#             */
/*   Updated: 2025/10/17 19:17:52 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// haal key uit "KEY_VALUE"
static char	*extract_key_copy(const char *pair, const char **out_value_start)
{
	const char	*equal_sign;
	size_t		key_len;
	char		*key_copy;

	if (!pair || !out_value_start)
		return (NULL);
	equal_sign = ft_strchr(pair, '=');
	if (equal_sign)
	{
		*out_value_start = equal_sign + 1;
		key_len = (size_t)(equal_sign - pair);
	}
	else
	{
		*out_value_start = "";
		key_len = ft_strlen(pair);
	}
	key_copy = (char *)malloc(key_len + 1);
	if (!key_copy)
		return (NULL);
	ft_memcpy(key_copy, pair, key_len);
	key_copy[key_len] = '\0';
	return (key_copy);
}

// loop over system_env, splits KEY=VALUE op eerste =, maak nodes en bouw lijst
t_env_entry	*env_load_from_environ(char **system_env)
{
	t_env_entry	*head;
	t_env_entry	*tmp;
	const char	*value_start;
	char		*key_copy;
	int			i;

	head = NULL;
	i = 0;
	while (system_env && system_env[i])
	{
		key_copy = extract_key_copy(system_env[i], &value_start);
		if (!key_copy)
			return (env_free_all(head), NULL);
		tmp = env_new_node(key_copy, value_start);
		free(key_copy);
		if (!tmp)
			return (env_free_all(head), NULL);
		env_append(&head, tmp);
		i++;
	}
	env_bump_shlvl(&head);
	return (head);
}
