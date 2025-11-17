/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:38:46 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/12 15:54:11 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// check: mag deze char in een env-naam zitten?
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

// lees de naam na een $ op positie i
const char	*expand_read_name(const char *s, int i, int *len_out)
{
	int	len;

	if (s[i] != '$')
		return (NULL);
	if (s[i + 1] == '?')
	{
		*len_out = 1;
		return (s + i + 1);
	}
	len = 0;
	while (s[i + 1 + len] && is_env_char(s[i + 1 + len]))
		len++;
	*len_out = len;
	return (s + i + 1);
}

// zoek VALUE voor NAME(len) in onze env-lijst
char	*expand_lookup_value(t_env_entry *env, const char *name, int len)
{
	extern int	g_exit_status;
	t_env_entry	*p;
	char		*status_str;

	if (!name || len <= 0)
		return (ft_strdup(""));
	
	// Special case voor $? - gebruik g_exit_status
	if (len == 1 && name[0] == '?')
	{
		status_str = ft_itoa(g_exit_status);
		if (!status_str)
			return (ft_strdup("0"));  // Fallback naar "0"
		return (status_str);
	}
	
	// Rest blijft hetzelfde
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

// vind eerste $ in s die gevolgd wordt door een geldige variabele naam
// FIXED: Only find $ that is followed by ? or valid identifier char
// This prevents infinite loop when encountering lone $ characters
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
			if (s[i + 1] == '?')
				return (i);
			if (is_env_char(s[i + 1]))
				return (i);
		}
		i++;
	}
	return (-1);
}
