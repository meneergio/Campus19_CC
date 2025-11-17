/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:26:18 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/01 23:26:18 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// maak 1 commando-node rond een tokenlijst
static t_commando	*parser_cmd_new(t_token *start)
{
	t_commando	*cmd;

	cmd = (t_commando *)malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->tokens = start;
	cmd->next = NULL;
	return (cmd);
}

// voeg commando achteraan toe
static int	parser_add_cmd(t_commando **head, t_commando **tail, t_token *start)
{
	t_commando	*node;

	node = parser_cmd_new(start);
	if (!node)
		return (0);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (1);
}

// helper: vind vorige node (zonder prev-pointer)
static t_token	*find_prev(t_token *start, t_token *node)
{
	t_token	*p;

	p = NULL;
	while (start && start != node)
	{
		p = start;
		start = start->next;
	}
	return (p);
}

// pipe geraakt: knip veilig, voeg blok toe, free pipe, zet start = na pipe
static t_token	*parser_pipe_hit(t_commando **head, t_commando **tail,
								t_token **start, t_token *pipe)
{
	t_token	*next;
	t_token	*prev;

	next = pipe->next;
	prev = find_prev(*start, pipe);
	if (!prev)
	{
		if (pipe->value)
			free(pipe->value);
		free(pipe);
		return (NULL);
	}
	prev->next = NULL;
	if (!parser_add_cmd(head, tail, *start))
	{
		if (pipe->value)
			free(pipe->value);
		free(pipe);
		return (NULL);
	}
	if (pipe->value)
		free(pipe->value);
	free(pipe);
	*start = next;
	return (next);
}

// maak van 1 token-lijst: cmd1 | cmd2 | cmd 3
t_commando	*parser_split_pipes(t_token *tok)
{
	t_commando	*head;
	t_commando	*tail;
	t_token		*start;
	t_token		*current;

	head = NULL;
	tail = NULL;
	start = tok;
	current = tok;
	while (current)
	{
		if (current->type == TOK_PIPE)
		{
			current = parser_pipe_hit(&head, &tail, &start, current);
			if (!current)
				return (parser_free_cmds(head), NULL);
		}
		else
			current = current->next;
	}
	if (start && !parser_add_cmd(&head, &tail, start))
		return (parser_free_cmds(head), NULL);
	return (head);
}
