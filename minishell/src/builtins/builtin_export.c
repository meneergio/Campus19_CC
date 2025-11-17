/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:47:37 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/12 16:03:29 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z') &&
		!(str[0] >= 'A' && str[0] <= 'Z') &&
		str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') &&
			!(str[i] >= 'A' && str[i] <= 'Z') &&
			!(str[i] >= '0' && str[i] <= '9') &&
			str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(const char *identifier)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, identifier, ft_strlen(identifier));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

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

static int	handle_export_assignment(char *arg, t_env_entry **env)
{
	char		*equals;
	char		*key;
	char		*value;
	char		*clean_value;
	t_env_entry	*node;
	t_env_entry	*new;

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
	node = env_find_node(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(clean_value);  // ← Maak een copy!
		free(clean_value);  // ← En free het origineel
	}
	else
	{
		new = env_new_node(key, clean_value);
		free(clean_value);
		env_append(env, new);
	}
	*equals = '=';
	return (0);
}

int	builtin_export(char **argv, t_env_entry **env)
{
	int			i;
	int			exit_code;
	char		*equals;
	t_env_entry	*p;

	if (!argv[1])
	{
		p = *env;
		while (p)
		{
			printf("declare -x %s=\"%s\"\n", p->key, p->value);
			p = p->next;
		}
		return (0);
	}
	exit_code = 0;
	i = 1;
	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals)
		{
			if (handle_export_assignment(argv[i], env) != 0)
				exit_code = 1;
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
			{
				print_export_error(argv[i]);
				exit_code = 1;
			}
		}
		i++;
	}
	return (exit_code);
}
