/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:49:12 by dzotti            #+#    #+#             */
/*   Updated: 2025/10/31 21:49:12 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// check als het < of << kan zijn
t_token	*lexer_try_redir_in(const char *s, int *i)
{
	if (s[*i] != '<')
		return (NULL);
	if (s[*i + 1] == '<')
	{
		*i += 2;
		return (token_new(TOK_HEREDOC, NULL));
	}
	*i += 1;
	return (token_new(TOK_REDIR_IN, NULL));
}

// check als het > of >> kan zijn
t_token	*lexer_try_redir_out(const char *s, int *i)
{
	if (s[*i] != '>')
		return (NULL);
	if (s[*i + 1] == '>')
	{
		*i += 2;
		return (token_new(TOK_APPEND, NULL));
	}
	*i += 1;
	return (token_new(TOK_REDIR_OUT, NULL));
}
