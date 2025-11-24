/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:29:24 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 21:29:24 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// mag deze char in een env-naam zitten? [A-Za-z0-9_]
int	is_env_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static char	*expand_status_value(int status)
{
	char	*s;

	s = ft_itoa(status);
	if (!s)
		return (ft_strdup("0"));
	return (s);
}

static char	*expand_pid_value(void)
{
	char	*s;
	pid_t	pid;

	pid = getpid();
	s = ft_itoa((int)pid);
	if (!s)
		return (ft_strdup(""));
	return (s);
}

// zoek VALUE voor NAME(len) in onze env-lijst
// speciale gevallen: $?  $$  $<digit>
char	*expand_lookup_value(t_env_entry *env, const char *name, int len)
{
	extern int	g_exit_status;
	t_env_entry	*p;

	if (!name || len <= 0)
		return (ft_strdup(""));
	if (len == 1 && name[0] == '?')
		return (expand_status_value(g_exit_status));
	if (len == 1 && name[0] == '$')
		return (expand_pid_value());
	if (len == 1 && ft_isdigit((unsigned char)name[0]))
		return (ft_strdup(""));
	p = env;
	while (p)
	{
		if ((int)ft_strlen(p->key) == len
			&& ft_strncmp(p->key, name, len) == 0)
			return (ft_strdup(p->value));
		p = p->next;
	}
	return (ft_strdup(""));
}

// vind eerste $ in s die gevolgd wordt door geldige var:
// $?  $$  $<digit>  of $IDENT
int	expand_find_dollar(const char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?' || s[i + 1] == '$'
				|| is_env_char(s[i + 1])
				|| ft_isdigit((unsigned char)s[i + 1]))
				return (i);
		}
		i++;
	}
	return (-1);
}
