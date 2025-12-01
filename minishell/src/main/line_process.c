/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 20:54:14 by dzotti            #+#    #+#             */
/*   Updated: 2025/12/01 18:17:15 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Haalt trailing '\n' weg uit een lijn
static void	trim_trailing_newline(char *s)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	if (i && s[i - 1] == '\n')
		s[i - 1] = '\0';
}

// Tokenize en expandeer de input-lijn.
static int	lex_and_expand(char *line, t_env_entry **env_head,
							t_token **tokens, int last_status)
{
	*tokens = lex_line(line);
	if (!*tokens)
		return (0);
	expand_tokens(*tokens, *env_head, last_status);
	return (1);
}

// Controleer syntax, split op pipes en bouw commandostructuur op.
static int	parse_and_build_cmds(t_token *tokens, t_commando **cmds)
{
	if (!parser_check_redir_syntax(tokens))
	{
		token_list_free(tokens);
		return (0);
	}
	if (!parser_check_pipe_syntax(tokens))
	{
		token_list_free(tokens);
		return (0);
	}
	*cmds = parser_split_pipes(tokens);
	if (!*cmds)
	{
		token_list_free(tokens);
		return (0);
	}
	if (!parser_build_cmd(*cmds))
	{
		token_list_free(tokens);
		parser_free_cmds(*cmds);
		return (0);
	}
	return (1);
}

// De eigenlijke verwerking, inclusief parsen, uitvoeren en opruimen.
static void	parse_execute_and_free(t_token *tokens, t_commando *cmds,
	t_env_entry **env_head, int *last_status)
{
	t_ast	ast;

	if (!parse_pipeline(cmds, &ast))
	{
		parser_free_cmds(cmds);
		token_list_free(tokens);
		return ;
	}
	if (!prepare_heredocs(&ast, *env_head, *last_status))
	{
		*last_status = 130;
		free_ast(&ast);
		parser_free_cmds(cmds);
		return ;
	}
	execute_ast(&ast, env_head, last_status);
	free_ast(&ast);
	parser_free_cmds(cmds);
}

// Verwerkt 1 lijn: parse, heredocs, execute, status en free
void	process_one_line(char *line, t_env_entry **env_head, int *last_status)
{
	t_token		*tokens;
	t_commando	*cmds;

	if (!line || !*line)
		return ;
	trim_trailing_newline(line);
	if (!lex_and_expand(line, env_head, &tokens, *last_status))
		return ;
	if (!parse_and_build_cmds(tokens, &cmds))
		return ;
	parse_execute_and_free(tokens, cmds, env_head, last_status);
}
