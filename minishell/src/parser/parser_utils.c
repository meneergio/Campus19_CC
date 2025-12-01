/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:11:50 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 16:49:07 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// is dit een redirect-token?
static int	is_redir_token(t_token *t)
{
	if (!t)
		return (0);
	if (t->type == TOK_REDIR_IN)
		return (1);
	if (t->type == TOK_REDIR_OUT)
		return (1);
	if (t->type == TOK_HEREDOC)
		return (1);
	if (t->type == TOK_APPEND)
		return (1);
	return (0);
}

// check voor dingen als: "ls >", "cat <", "echo hi >"
// return 1 = ok, 0 = syntax error
int	parser_check_redir_syntax(t_token *tok)
{
	t_token	*cur;

	cur = tok;
	while (cur)
	{
		if (is_redir_token(cur))
		{
			if (!cur->next || cur->next->type != TOK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near redirection\n", 2);
				return (0);
			}
		}
		cur = cur->next;
	}
	return (1);
}
