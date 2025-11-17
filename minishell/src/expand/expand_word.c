/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:51:34 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/12 17:32:14 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// maak kopie van s[0..end-1]
static char	*dup_prefix(const char *s, int end)
{
	char	*out;

	out = (char *)malloc(end + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s, end);
	out[end] = '\0';
	return (out);
}

// maak kopie van s vanaf start
static char	*dup_suffix(const char *s, int start)
{
	size_t	len;
	char	*out;

	len = ft_strlen(s + start);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	return (out);
}

// plak 3 stukken aan elkaar en free alle 3
static char	*join_three(char *a, char *b, char *c)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(a, b);
	free(a);
	free(b);
	if (!tmp)
	{
		free(c);
		return (NULL);
	}
	res = ft_strjoin(tmp, c);
	free(tmp);
	free(c);
	if (!res)
		return (NULL);
	return (res);
}

// doe in 1 string: ..$VAR.. -> ..VALUE.. : before + value + after
// Note: expand_find_dollar now only returns $ positions that are followed
// by valid variable names, so we don't need extra checks here
char	*expand_word_once(const char *s, t_env_entry *env)
{
	t_expword	e;

	e.dollar_i = expand_find_dollar(s);
	if (e.dollar_i < 0)
		return (ft_strdup(s));
	e.name = expand_read_name(s, e.dollar_i, &e.name_len);
	if (!e.name)
		return (ft_strdup(s));
	e.before = dup_prefix(s, e.dollar_i);
	e.value = expand_lookup_value(env, e.name, e.name_len);
	e.after = dup_suffix(s, e.dollar_i + 1 + e.name_len);
	if (!e.before || !e.value || !e.after)
	{
		free(e.before);
		free(e.value);
		free(e.after);
		return (NULL);
	}
	return (join_three(e.before, e.value, e.after));
}

// herhaal tot er geen $ meer staat
char	*expand_word_all(const char *s, t_env_entry *env)
{
	char	*current;
	char	*next;

	current = ft_strdup(s);
	if (!current)
		return (NULL);
	while (expand_find_dollar(current) >= 0)
	{
		next = expand_word_once(current, env);
		if (!next)
			break ;
		free(current);
		current = next;
	}
	return (current);
}
