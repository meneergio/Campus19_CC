/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_assignment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:19:39 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/19 16:56:52 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// verwijder omringende quotes uit value indien aanwezig
static char	*remove_quotes_from_value(const char *value)
{
	size_t	len;
	char	*result;

	if (!value || !*value)
		return (ft_strdup(""));
	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		result = (char *)malloc(len - 1);
		if (!result)
			return (NULL);
		ft_memcpy(result, value + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (ft_strdup(value));
}

// interne helper: update env met key / value
static int	export_update_env(t_env_entry **env, char *key, char *clean_value)
{
	t_env_entry	*node;

	node = env_find_node(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(clean_value);
		return (0);
	}
	node = env_new_node(key, clean_value);
	if (!node)
		return (1);
	env_append(env, node);
	return (0);
}

// interne helper: valideer key en herstel '=' bij fout
static int	export_check_key(char *key, char *equals)
{
	if (!is_valid_identifier(key))
	{
		print_export_error(key);
		*equals = '=';
		return (0);
	}
	return (1);
}

// verwerk één KEY=VALUE argument voor export
int	handle_export_assignment(char *arg, t_env_entry **env)
{
	char	*equals;
	char	*key;
	char	*value;
	char	*clean_value;
	int		result;

	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	*equals = '\0';
	key = arg;
	value = equals + 1;
	if (!export_check_key(key, equals))
		return (1);
	clean_value = remove_quotes_from_value(value);
	if (!clean_value)
	{
		*equals = '=';
		return (1);
	}
	result = export_update_env(env, key, clean_value);
	free(clean_value);
	*equals = '=';
	return (result);
}
