/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:36:21 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/12 14:20:00 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// telt aantal argv-woorden (redir-targets tellen niet mee)
static int	count_argv_words(t_token *t)
{
	int	pending;
	int	count;

	pending = -1;
	count = 0;
	while (t && t->type != TOK_PIPE)
	{
		if (pending == -1 && t->type == TOK_WORD)
		{
			// Skip lege values van $EMPTY expansion
			if (t->value && t->value[0] != '\0')
				count++;
		}
		else if (pending != -1 && t->type == TOK_WORD)
			pending = -1;
		else if (t->type == TOK_REDIR_IN)
			pending = R_IN;
		else if (t->type == TOK_REDIR_OUT)
			pending = R_OUT;
		else if (t->type == TOK_APPEND)
			pending = R_APPEND;
		else if (t->type == TOK_HEREDOC)
			pending = R_HEREDOC;
		t = t->next;
	}
	return (count);
}

// check 1 commando: elke redirection moet direct gevolgd worden door een WORD
static int	validate_one_cmd(t_token *t)
{
	int	pending;

	pending = -1;
	while (t && t->type != TOK_PIPE)
	{
		if (pending == -1 && t->type == TOK_WORD)
			;  // OK
		else if (pending != -1 && t->type == TOK_WORD)
			pending = -1;
		else if (t->type == TOK_REDIR_IN)
			pending = R_IN;
		else if (t->type == TOK_REDIR_OUT)
			pending = R_OUT;
		else if (t->type == TOK_APPEND)
			pending = R_APPEND;
		else if (t->type == TOK_HEREDOC)
			pending = R_HEREDOC;
		t = t->next;
	}
	if (pending != -1)  // Alleen check pending, niet argc
		return (0);
	return (1);
}

// vul argv-array met WORDS; redir-targets overslaan
static int	fill_argv_words(t_token *t, char **argv_array)
{
	int	pending;
	int	i;

	pending = -1;
	i = 0;
	while (t && t->type != TOK_PIPE)
	{
		if (pending == -1 && t->type == TOK_WORD)
		{
			// Skip lege values
			if (t->value && t->value[0] != '\0')
			{
				argv_array[i] = t->value;
				t->value = NULL;
				i++;
			}
		}
		else if (t->type == TOK_WORD && pending != -1)
			pending = -1;
		else
			redir_set_pending(&pending, t);
		t = t->next;
	}
	argv_array[i] = NULL;
	return (1);
}

// bouw argv voor 1 commando (malloc + vullen)
static int	build_argv_for_one(t_commando *cmd)
{
	int		argv_count;
	char	**argv_array;

	argv_count = count_argv_words(cmd->tokens);
	if (argv_count == 0)
	{
		cmd->argv = NULL;
		return (1);
	}
	argv_array = (char **)malloc(sizeof(char *) * (argv_count + 1));
	if (!argv_array)
		return (0);
	if (!fill_argv_words(cmd->tokens, argv_array))
	{
		free(argv_array);
		return (0);
	}
	cmd->argv = argv_array;
	return (1);
}

// loop over alle commando's: valideren + argv bouwen + redirs bouwen
int	parser_build_cmd(t_commando *head)
{
	t_commando	*c;

	c = head;
	while (c)
	{
		c->argv = NULL;
		c->redirs = NULL;
		if (!validate_one_cmd(c->tokens))
			return (0);
		if (!build_argv_for_one(c))
			return (0);
		if (!build_redirs_for_one(c))
			return (0);
		c = c->next;
	}
	return (1);
}
