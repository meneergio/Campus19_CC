/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:50:56 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/12 16:16:57 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// maak nieuwe token met type + value
t_token	*token_new(t_toktype type, char *value)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = value;
	t->next = NULL;
	t->no_expand = 0;
	return (t);
}

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

// 1 token lezen op positie i
static t_token	*lex_one(const char *s, int *i)
{
	t_token	*new;

	skip_spaces(s, i);
	if (s[*i] == '\0')
		return (NULL);
	if (s[*i] == '|')
	{
		new = token_new(TOK_PIPE, NULL);
		(*i)++;
		return (new);
	}
	new = lexer_try_redir_in(s, i);
	if (new)
		return (new);
	new = lexer_try_redir_out(s, i);
	if (new)
		return (new);
	return (lexer_read_word(s, i));
}

// volledige lijn -> lijst tokens
t_token	*lex_line(const char *line)
{
	t_token		head;
	t_token		*tail;
	t_token		*new;
	t_toktype	last_type;
	int			i;

	head.next = NULL;
	tail = &head;
	last_type = -1;
	i = 0;
	while (line && line[i])
	{
		new = lex_one(line, &i);
		if (!new)
		{
			token_list_free(head.next);
			return (NULL);
		}
		if (last_type == TOK_HEREDOC && new->type == TOK_WORD)
			new->no_expand = 1;
		tail->next = new;
		tail = new;
		last_type = new->type;
	}
	return (head.next);
}
