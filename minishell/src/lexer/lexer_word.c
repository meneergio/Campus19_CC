/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:37:26 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/26 16:37:35 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*str_join_free(char *base, char *add)
{
	char	*joined;

	if (!add)
		return (free(base), NULL);
	if (!base)
		return (add);
	joined = ft_strjoin(base, add);
	free(base);
	free(add);
	return (joined);
}

static char	*read_plain_part(const char *s, int *i)
{
	int		start;
	int		len;
	char	*out;

	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '|'
		&& s[*i] != '<' && s[*i] != '>' && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	len = *i - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	return (out);
}

static char	*lexer_add_quoted_part(char **acc, t_lexflags *f,
				const char *s, int *i)
{
	char	*part;

	f->had_quotes = 1;
	if (s[*i] == '\'')
	{
		part = lexer_read_squote(s, i);
		if ((*acc)[0] != '\0')
			f->mixed = 1;
		f->saw_squote = 1;
	}
	else
		part = lexer_read_dquote(s, i);
	if (f->saw_squote && s[*i - 1] == '"')
		f->mixed = 1;
	return (part);
}

int	lexer_add_part(char **acc, t_lexflags *f, const char *s, int *i)
{
	char	*part;

	if (s[*i] == '\'' || s[*i] == '"')
		part = lexer_add_quoted_part(acc, f, s, i);
	else
	{
		part = read_plain_part(s, i);
		if (f->saw_squote || f->had_quotes)
			f->mixed = 1;
	}
	*acc = str_join_free(*acc, part);
	if (!*acc)
		return (0);
	return (1);
}

t_token	*lexer_read_word(const char *s, int *i)
{
	char		*acc;
	t_token		*token;
	t_lexflags	f;

	acc = ft_strdup("");
	if (!acc)
		return (NULL);
	f.saw_squote = 0;
	f.mixed = 0;
	f.had_quotes = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '|'
		&& s[*i] != '<' && s[*i] != '>')
	{
		if (!lexer_add_part(&acc, &f, s, i))
			return (NULL);
	}
	token = token_new(TOK_WORD, acc);
	if (!token)
		free(acc);
	else if (f.saw_squote && !f.mixed)
		token->no_expand = 1;
	if (token)
		token->had_any_quotes = f.had_quotes;
	return (token);
}
