/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:21:21 by dzotti            #+#    #+#             */
/*   Updated: 2025/10/31 22:21:21 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// lees '...' -> geef inhoud terug zonder ' ' quotes
char	*lexer_read_squote(const char *s, int *i)
{
	int		start;
	int		len;
	char	*out;

	if (s[*i] != '\'')
		return (NULL);
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'')
		return (NULL);
	len = *i - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	(*i)++;
	return (out);
}

// lees "..." -> geef inhoud terug zonder " " quotes
char	*lexer_read_dquote(const char *s, int *i)
{
	int		start;
	int		len;
	char	*out;

	if (s[*i] != '"')
		return (NULL);
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	if (s[*i] != '"')
		return (NULL);
	len = *i - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	(*i)++;
	return (out);
}
