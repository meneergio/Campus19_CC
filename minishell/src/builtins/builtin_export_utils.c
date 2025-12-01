/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:50:19 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/17 18:50:19 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// schrijf value in bestaande of nieuwe env-node
static void	export_store_value(t_env_entry **env,
			t_env_entry *node, const char *key, const char *clean_value)
{
	t_env_entry	*new_node;

	if (node)
	{
		free(node->value);
		node->value = ft_strdup(clean_value);
	}
	else
	{
		new_node = env_new_node(key, clean_value);
		if (new_node)
			env_append(env, new_node);
	}
}

// verwerk één KEY=VALUE argument voor export
int	handle_export_assignment(char *arg, t_env_entry **env)
{
	char		*equals;
	char		*key;
	char		*value;
	char		*clean_value;
	t_env_entry	*node;

	equals = ft_strchr(arg, '=');
	*equals = '\0';
	key = arg;
	value = equals + 1;
	if (!is_valid_identifier(key))
	{
		print_export_error(key);
		*equals = '=';
		return (1);
	}
	clean_value = remove_quotes_from_value(value);
	if (!clean_value)
		return (*equals = '=', 1);
	node = env_find_node(*env, key);
	export_store_value(env, node, key, clean_value);
	free(clean_value);
	*equals = '=';
	return (0);
}
