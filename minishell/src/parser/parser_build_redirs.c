/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:21:27 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/26 16:45:34 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// maak 1 redir-node met no_expand flag
static t_redir	*redir_new(t_rtype type, char *arg_owned, int no_expand)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->arg = arg_owned;
	node->next = NULL;
	node->hdoc_fd = -1;
	node->no_expand = no_expand;
	return (node);
}

// append redir-node achteraan
static void	redir_append(t_redir **head, t_redir **tail, t_redir *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

// als pending <,<<,>,>> is en huidig token WORD is
static int	redir_consume_pending(int *pending, t_token *tok,
									t_redir **head, t_redir **tail)
{
	t_redir	*node;

	if (*pending == -1)
		return (1);
	if (!tok || tok->type != TOK_WORD)
		return (0);
	node = redir_new((t_rtype)(*pending), tok->value, tok->had_any_quotes);
	if (!node)
		return (0);
	tok->value = NULL;
	redir_append(head, tail, node);
	*pending = -1;
	return (1);
}

// bouw redirs-lijst uit token verplaats targets naar t_redir
int	build_redirs_for_one(t_commando *command)
{
	int		pending;
	t_token	*cur;
	t_redir	*head;
	t_redir	*tail;

	cur = command->tokens;
	pending = -1;
	head = NULL;
	tail = NULL;
	while (cur && cur->type != TOK_PIPE)
	{
		if (cur->type == TOK_WORD && pending != -1)
		{
			if (!redir_consume_pending(&pending, cur, &head, &tail))
				return (0);
		}
		else
			redir_set_pending(&pending, cur);
		cur = cur->next;
	}
	command->redirs = head;
	return (1);
}
