/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:10:57 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/24 13:44:06 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// update of toevoegen van env-variabele
static int	update_env_var(t_env_entry **env, const char *key, const char *val)
{
	t_env_entry	*p;
	t_env_entry	*new_node;

	p = *env;
	while (p)
	{
		if (ft_strncmp(p->key, key, ft_strlen(key) + 1) == 0)
		{
			free(p->value);
			p->value = ft_strdup(val);
			if (!p->value)
				return (-1);
			return (0);
		}
		p = p->next;
	}
	new_node = env_new_node(key, val);
	if (!new_node)
		return (-1);
	env_append(env, new_node);
	return (0);
}

// haal doelpad voor cd (HOME of argv[1])
static char	*get_target_path(char **argv, t_env_entry *env)
{
	const char	*home;

	if (!argv[1])
	{
		home = env_find_value(env, "HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (NULL);
		}
		return (ft_strdup(home));
	}
	return (ft_strdup(argv[1]));
}

// haal huidige directory in old_cwd
static int	get_old_cwd(char *old_cwd, size_t size)
{
	if (getcwd(old_cwd, size) == NULL)
	{
		perror("cd: error getting current directory");
		return (1);
	}
	return (0);
}

// voer chdir uit en update PWD/OLDPWD in env
static int	change_dir_and_update_env(char *target_path, char *old_cwd,
										t_env_entry **env)
{
	char	new_cwd[PATH_MAX];

	if (chdir(target_path) != 0)
	{
		perror(target_path);
		return (1);
	}
	if (getcwd(new_cwd, sizeof(new_cwd)) == NULL)
	{
		perror("cd: error getting new current directory");
		return (1);
	}
	if (update_env_var(env, "OLDPWD", old_cwd) == -1)
		return (1);
	if (update_env_var(env, "PWD", new_cwd) == -1)
		return (1);
	return (0);
}

// verander directory en update env
int	builtin_cd(char **argv, t_env_entry **env)
{
	char	*target_path;
	char	old_cwd[PATH_MAX];

	if (argv[1] && argv[2])
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 24);
		return (1);
	}
	if (get_old_cwd(old_cwd, sizeof(old_cwd)))
		return (1);
	target_path = get_target_path(argv, *env);
	if (!target_path)
		return (1);
	if (change_dir_and_update_env(target_path, old_cwd, env))
	{
		free(target_path);
		return (1);
	}
	free(target_path);
	return (0);
}
