/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:48:41 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 15:36:22 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stel 'pending' in op de juiste redirect-type op basis van het token
// pending = -1 betekent: geen openstaande redirect
void	redir_set_pending(int *pending, t_token *tok)
{
	if (!pending || !tok)
		return ;
	if (tok->type == TOK_REDIR_IN)
		*pending = R_IN;
	else if (tok->type == TOK_REDIR_OUT)
		*pending = R_OUT;
	else if (tok->type == TOK_HEREDOC)
		*pending = R_HEREDOC;
	else if (tok->type == TOK_APPEND)
		*pending = R_APPEND;
}
