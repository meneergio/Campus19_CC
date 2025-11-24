/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:10:39 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/18 15:26:38 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// check identifier syntaxi
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&& !(str[0] >= 'A' && str[0] <= 'Z')
		&& str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_error(const char *identifier)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, identifier, ft_strlen(identifier));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

// Zorgt ervoor dat variabelen zonder '=' een NULL-waarde krijgen.
static void	ensure_env_var(t_env_entry **env, const char *key)
{
	t_env_entry	*node;

	node = env_find_node(*env, key);
	if (node)
		return ;
	node = env_new_node(key, NULL);
	if (!node)
		return ;
	env_append(env, node);
}

static int	export_process_args(char **argv, t_env_entry **env)
{
	int		i;
	int		exit_code;
	char	*equals;

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
		else if (!is_valid_identifier(argv[i]))
		{
			print_export_error(argv[i]);
			exit_code = 1;
		}
		else
			ensure_env_var(env, argv[i]);
		i++;
	}
	return (exit_code);
}

// Afhandeling van 'export' zonder argumenten, toont correcte output.
int	builtin_export(char **argv, t_env_entry **env)
{
	t_env_entry	*p;

	if (!argv[1])
	{
		p = *env;
		while (p)
		{
			if (p->value)
				printf("declare -x %s=\"%s\"\n", p->key, p->value);
			else
				printf("declare -x %s\n", p->key);
			p = p->next;
		}
		return (0);
	}
	return (export_process_args(argv, env));
}
