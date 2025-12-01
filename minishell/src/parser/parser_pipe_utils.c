/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:01:01 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 21:01:01 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// helper: is dit een pipe-token?
static int	is_pipe_token(t_token *t)
{
	if (!t)
		return (0);
	return (t->type == TOK_PIPE);
}

// check dingen als: "| ls", "ls |", "cmd1 || cmd2"
// return 1 = ok, 0 = syntax error
int	parser_check_pipe_syntax(t_token *tok)
{
	t_token	*cur;

	if (!tok)
		return (1);
	if (is_pipe_token(tok))
	{
		ft_putstr_fd("minishell: syntax error near pipe\n", 2);
		return (0);
	}
	cur = tok;
	while (cur)
	{
		if (is_pipe_token(cur)
			&& (!cur->next || is_pipe_token(cur->next)))
		{
			ft_putstr_fd("minishell: syntax error near pipe\n", 2);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}
