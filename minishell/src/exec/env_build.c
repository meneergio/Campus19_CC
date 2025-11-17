/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:13:06 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/03 16:13:09 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	count_env_entries(t_env_entry *env)
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

static char	*make_env_string(const char *key, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

char	**build_envp(t_env_entry *env)
{
	char		**envp;
	t_env_entry	*p;
	int			count;
	int			i;

	count = count_env_entries(env);
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	p = env;
	i = 0;
	while (p)
	{
		envp[i] = make_env_string(p->key, p->value);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			return (free(envp), NULL);
		}
		p = p->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
