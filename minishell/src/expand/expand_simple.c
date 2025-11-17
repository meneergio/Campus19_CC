/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:37:31 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/01 12:37:31 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// vervang token->value als het exact $NAAM is
int	expand_token_simple(t_token *tok, t_env_entry *env)
{
	const char	*name;
	char		*value;
	int			name_len;

	if (!tok || !tok->value)
		return (0);
	if (tok->value[0] != '$')
		return (0);
	name = expand_read_name(tok->value, 0, &name_len);
	if (!name)
		return (0);
	value = expand_lookup_value(env, name, name_len);
	if (!value)
		return (-1);
	free(tok->value);
	tok->value = value;
	return (0);
}
