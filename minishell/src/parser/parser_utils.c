/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:23:30 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/04 13:23:30 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_set_pending(int *pending, t_token *tok)
{
	if (*pending != -1)
		return ;
	if (tok->type == TOK_REDIR_IN)
		*pending = R_IN;
	else if (tok->type == TOK_REDIR_OUT)
		*pending = R_OUT;
	else if (tok->type == TOK_APPEND)
		*pending = R_APPEND;
	else if (tok->type == TOK_HEREDOC)
		*pending = R_HEREDOC;
}
