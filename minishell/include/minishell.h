/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:41:05 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/25 14:43:04 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>

/* ===== Global ==== */
extern int	g_exit_status;

/* ===== Types ===== */

typedef struct s_env_entry
{
	char				*key;
	char				*value;
	struct s_env_entry	*next;
}	t_env_entry;

typedef enum e_toktype
{
	TOK_WORD = 0,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	int				no_expand;
	struct s_token	*next;
}	t_token;

typedef struct s_lexflags
{
	int	saw_squote;
	int	mixed;
}	t_lexflags;

typedef struct s_expword
{
	int			dollar_i;
	const char	*name;
	int			name_len;
	char		*before;
	char		*value;
	char		*after;
}	t_expword;

typedef enum e_rtype
{
	R_IN = 0,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
	char			*arg;
	int				hdoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command_data
{
	char	**argv;
	t_redir	*redirs;
}	t_command_data;

typedef struct s_ast
{
	int				ncmd;
	t_command_data	*cmdv;
}	t_ast;

typedef struct s_commando
{
	t_token				*tokens;
	char				**argv;
	t_redir				*redirs;
	struct s_commando	*next;
}	t_commando;

/* Context voor pipeline-executie (execute_pipeline.c) */
typedef struct s_pipe_ctx
{
	t_ast		*ast;
	t_env_entry	**env;
	int			(*pipes)[2];
	pid_t		*pids;
	int			*last_status;
	pid_t		first_pgid;
	pid_t		shell_pgid;
}	t_pipe_ctx;

/* ===== Main / status / line- en bufferverwerking ===== */

void		update_exit_status_env(t_env_entry **env, int status);
void		process_buffer(char *buf, t_env_entry **env_head, int *last_status);
void		process_one_line(char *line, t_env_entry **env_head,
				int *last_status);
void		expand_tokens(t_token *tok, t_env_entry *env);

/* ===== Env ===== */

t_env_entry	*env_new_node(const char *key, const char *value);
void		env_append(t_env_entry **head, t_env_entry *new_node);
void		env_free_all(t_env_entry *head);
const char	*env_find_value(t_env_entry *env, const char *key);
t_env_entry	*env_find_node(t_env_entry *head, const char *key);
t_env_entry	*env_load_from_environ(char **environ);
void		env_bump_shlvl(t_env_entry **env);

/* ===== Lexer ===== */

t_token		*token_new(t_toktype type, char *value);
void		token_list_free(t_token *head);
void		token_append(t_token **head, t_token *new_node);
t_token		*lexer_try_redir_in(const char *s, int *i);
t_token		*lexer_try_redir_out(const char *s, int *i);
t_token		*lexer_read_word(const char *s, int *i);
char		*lexer_read_squote(const char *s, int *i);
char		*lexer_read_dquote(const char *s, int *i);
t_token		*lex_line(const char *line);

/* ===== Expand ===== */

char		*expand_word_all(const char *s, t_env_entry *env);
const char	*expand_read_name(const char *s, int start_i, int *len);
char		*expand_lookup_value(t_env_entry *env, const char *name, int len);
int			expand_find_dollar(const char *s);
char		*strip_all_quotes(char *original_str);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_append_char(char *s, char c);
int			expand_status_on_list(t_commando *head, int last_status);
int			is_env_char(char s);

/* ===== Parser ===== */

int			parser_build_cmd(t_commando *cmd_list);
int			parse_pipeline(t_commando *cmd_list, t_ast *out);
void		parser_free_cmds(t_commando *cmd);
void		free_ast(t_ast *ast);
void		redir_set_pending(int *pending, t_token *tok);
t_commando	*parser_split_pipes(t_token *tokens);
int			parser_build_redirs(t_commando *cmd_list);
int			build_redirs_for_one(t_commando *cmd);
int			parser_check_redir_syntax(t_token *tok);
int			parser_check_pipe_syntax(t_token *tok);

/* ===== Heredoc ===== */

int			prepare_heredocs(t_ast *ast, t_env_entry *env, int last_status);
int			read_heredoc_input(const char *delim, int hdoc_fd_writen,
				t_env_entry *env);
void		cleanup_opened_heredocs(t_ast *ast, int up_to_cmd);
int			prepare_heredocs_one_cmd(t_redir *r, t_env_entry *env);
int			handle_one_heredoc(t_redir *r, t_env_entry *env);
void		close_all_heredoc_fds(t_ast *ast);

/* ===== Builtins ===== */

int			is_builtin(const char *cmd);
int			run_builtin(char **argv, t_env_entry **env, int last_status);
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_env_entry **env);
int			builtin_pwd(void);
int			builtin_env(t_env_entry *env);
int			builtin_exit(char **argv, int last_status, t_env_entry *env);
int			builtin_export(char **argv, t_env_entry **env);
int			builtin_unset(char **argv, t_env_entry **env);
int			is_numeric(const char *s);

/* export helpers */

int			handle_export_assignment(char *arg, t_env_entry **env);
int			is_valid_identifier(const char *str);
void		print_export_error(const char *identifier);

/* ===== Executor ===== */

char		*resolve_cmd_path(const char *cmd, t_env_entry *env);
char		**build_envp(t_env_entry *env);
void		free_envp(char **envp);
int			apply_redirs(t_redir *redirs);

void		handle_child_status(int status, int *last_status);
int			execute_single(t_ast *ast, t_env_entry **env, int *last_status);
int			execute_pipeline(t_ast *ast, t_env_entry **env, int *last_status);
int			execute_ast(t_ast *ast, t_env_entry **env, int *last_status);
void		execute_external_cmd(t_command_data *cmd, t_env_entry **env);

/* pipeline utils (execute_pipeline_utils.c) */
void		close_all_pipes(int count, int (*pipes)[2]);
void		wait_spawned_children(int spawned, pid_t *pids);
void		set_child_pgid(pid_t pid, pid_t *first_pgid, int index);
int			free_pipe_data(int (*pipes)[2], pid_t *pids);

/* ===== Signals / terminal / prompt ===== */

void		setup_prompt_signal_handlers(void);
int			shell_get_signal(void);
void		shell_set_signal(int sig);

int			terminal_hide_control_chars(void);
int			terminal_restore_control_chars(void);
int			terminal_enable_control_chars(void);

char		*read_prompt_line(void);
char		*read_prompt(const char *prompt);

#endif
