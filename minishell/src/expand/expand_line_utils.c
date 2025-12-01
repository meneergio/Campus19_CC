/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:49:50 by gwindey           #+#    #+#             */
/*   Updated: 2025/12/01 16:04:32 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Expandeert één token met $ op basis van de env
static void	expand_one_token(t_token *tok, t_env_entry *env, int last_status)
{
	char	*newv;

	if (tok->type != TOK_WORD)
		return ;
	if (tok->no_expand || !tok->value)
		return ;
	if (expand_find_dollar(tok->value) < 0)
		return ;
	newv = expand_word_all(tok->value, env, last_status);
	if (!newv)
		return ;
	free(tok->value);
	tok->value = newv;
}

// Loopt over alle tokens en doet expansie waar nodig
void	expand_tokens(t_token *tok, t_env_entry *env, int last_status)
{
	while (tok)
	{
		expand_one_token(tok, env, last_status);
		tok = tok->next;
	}
}
