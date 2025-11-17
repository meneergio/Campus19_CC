/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:10:57 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/14 15:01:06 by gwindey          ###   ########.fr       */
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
	// OPMERKING: ft_strlen(key) kan hier beter buiten de lus staan voor efficiëntie.
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
	// Optioneel: voeg hier de logica voor 'cd -' toe als je dat wilt implementeren.
	return (ft_strdup(argv[1]));
}

int	builtin_cd(char **argv, t_env_entry **env)
{
	char	*target_path;
	char	old_cwd[PATH_MAX];
	char	new_cwd[PATH_MAX];

	// START AANPASSING VOOR TEST 40
	// Controleer op te veel argumenten, wat Bash doet in deze situatie
	if (argv[1] && argv[2])
	{
		// De foutmelding van bash is korter op deze test, zonder de 'cd: ' prefix,
		// maar om het veiliger te maken repliceren we de korte fout van de tester.
		// De tester verwacht: " too many arguments" (van bash)
		// Jouw minishell moet een exit code van 1 geven.
		write(STDERR_FILENO, "cd: too many arguments\n", 23); // Dit is de standaard 'sh' fout.
		return (1);
	}
	// EINDE AANPASSING

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("cd: error getting current directory");
		return (1);
	}
	target_path = get_target_path(argv, *env);
	if (!target_path)
		return (1);
	if (chdir(target_path) != 0)
	{
		perror(target_path);
		free(target_path);
		return (1);
	}
	free(target_path);
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
