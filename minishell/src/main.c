/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:24 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/14 16:06:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern char	**environ;
int	g_exit_status = 0;

// DEZE FUNCTIE IS VERWIJDERD
/*
void	update_exit_status_env(t_env_entry **env, int status)
{
	(void)env;  // We gebruiken env niet meer
	g_exit_status = status;  // Update alleen global
}
*/

/* strip trailing '\n' uit 1 regel (veiligheid) */
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

/* expand alle WORD tokens met $ (behalve no_expand) */
static void	expand_tokens(t_token *tok, t_env_entry *env_head)
{
	char	*newv;

	while (tok)
	{
		if (tok->type == TOK_WORD && !tok->no_expand
			&& tok->value && expand_find_dollar(tok->value) >= 0)
		{
			newv = expand_word_all(tok->value, env_head);
			if (newv)
			{
				free(tok->value);
				tok->value = newv;
			}
		}
		tok = tok->next;
	}
}
/* verwerk 1 shell-regel: lex -> expand -> parser -> execute -> free */

static void process_one_line(char *line, t_env_entry **env_head, int *last_status)
{
	t_token	*tokens;
	t_commando	*cmds;
	t_ast	ast;

	if (!line || !*line)
		return ;
	trim_trailing_newline(line);
	tokens = lex_line(line);
	if (!tokens)
			return;
	expand_tokens(tokens, *env_head);
	cmds = parser_split_pipes(tokens);
	if (!cmds)
	{
		token_list_free(tokens);
		return ((void)printf("minishell: syntax error near pipe\n"));
	}
	if (!parser_build_cmd(cmds))
	{
		token_list_free(tokens);
		parser_free_cmds(cmds);
		return ((void)printf("minishell: syntax error near redirection\n"));
	}

	// Build AST and execute
	if (parse_pipeline(cmds, &ast))
	{
		prepare_heredocs(&ast, *env_head, *last_status);
		execute_ast(&ast, env_head, last_status);
		// AANGEPAST: Update g_exit_status direct
		g_exit_status = *last_status;
		free_ast(&ast);
	}

	parser_free_cmds(cmds);
	token_list_free(tokens);
}

/* split buffer op '\n' en verwerk elke niet-lege subregel */
static void	process_buffer(char *buf, t_env_entry **env_head, int *last_status)
{
	char	*p;
	char	*start;

	if (!buf || !*buf)
		return ;
	start = buf;
	p = buf;
	while (*p)
	{
		if (*p == '\n')
		{
			*p = '\0';
			if (*start)
				process_one_line(start, env_head, last_status);
			start = p + 1;
		}
		p++;
	}
	if (*start)
		process_one_line(start, env_head, last_status);
}

/* main loop: prompt, lees, verwerk, sluit netjes af */
int main(int argc, char **argv)
{
	t_env_entry	*env_head;
	char		*line;
	int			last_status;

	(void)argc;
	(void)argv;
	last_status = 0;
	env_head = env_load_from_environ(environ);
	env_bump_shlvl(&env_head);
	// AANGEPAST: Initialiseer g_exit_status direct
	g_exit_status = 0;

	while (1)
	{
		terminal_hide_control_chars();  //  Verberg tijdens prompt
		setup_prompt_signal_handlers();
		line = read_prompt_line();
		terminal_restore_control_chars();  //  Herstel tijdens execution

		if (!line)
			break ;
		process_buffer(line, &env_head, &last_status);
		free(line);
	}

	env_free_all(env_head);
	return (last_status);
}
