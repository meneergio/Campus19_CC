/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_read_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:52:23 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 21:52:23 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// lees de naam na een $ op positie i
// - $? -> len = 1
// - $$ -> len = 1
// - $<digit> -> len = 1
// - anders: zo lang mogelijk [A-Z a-z 0-9]

const char	*expand_read_name(const char *s, int i, int *len_out)
{
	int	start;
	int	len;

	*len_out = 0;
	if (!s || s[i] != '$')
		return (NULL);
	if (!s[i + 1])
		return (NULL);
	start = i + 1;
	if (s[start] == '?' || s[start] == '$'
		|| ft_isdigit((unsigned char)s[start]))
	{
		*len_out = 1;
		return (s + start);
	}
	len = 0;
	while (s[start + len] && is_env_char(s[start + len]))
		len++;
	*len_out = len;
	return (s + start);
}
