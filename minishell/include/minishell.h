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
# include <fcntl.h>
#include <errno.h>

/*============================*/
/* STRUCTS           */
/*============================*/

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
	t_toktype	type;
	char		*value;
	int			no_expand;
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
	t_rtype		type;
	char		*arg;
	int			hdoc_fd;
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
	t_token			*tokens;
	char			**argv;    // <-- TOEGEVOEGD: Argumenten array
	t_redir			*redirs;   // <-- TOEGEVOEGD: Redirection lijst
	struct s_commando	*next;
}	t_commando;

//MAIN
void	update_exit_status_env(t_env_entry **env, int status);

/*============================*/
/* ENV             */
/*============================*/

t_env_entry	*env_new_node(const char *key, const char *value);
void		env_append(t_env_entry **head, t_env_entry *new_node);
void		env_free_all(t_env_entry *head);
const char	*env_find_value(t_env_entry *env, const char *key);

// MISSING: Initial environment loading and shell level update
t_env_entry	*env_load_from_environ(char **environ);
void		env_bump_shlvl(t_env_entry **env);

t_env_entry	*env_find_node(t_env_entry *head, const char *key);

/*============================*/
/* LEXER           */
/*============================*/

t_token		*token_new(t_toktype type, char *value);
void		token_list_free(t_token *head);
void		token_append(t_token **head, t_token *new_node);

// Prototypes die de fouten oplossen:
t_token		*lexer_try_redir_in(const char *s, int *i);
t_token		*lexer_try_redir_out(const char *s, int *i);
t_token		*lexer_read_word(const char *s, int *i);

// Prototypes voor het lezen van aanhalingstekens (NIEUW):
char		*lexer_read_squote(const char *s, int *i);
char		*lexer_read_dquote(const char *s, int *i);

// Main function for tokenizing the input line
t_token		*lex_line(const char *line);

/*============================*/
/* EXPAND           */
/*============================*/

char	*expand_status_code(char *line, int last_status);

// Corrected prototype for expanding a single word/token
char		*expand_word_all(const char *s, t_env_entry *env);

// Prototypes die de fouten oplossen:
const char	*expand_read_name(const char *s, int start_i, int *len);
char		*expand_lookup_value(t_env_entry *env, const char *name, int len);

// Deze functie is nu verplaatst naar hier:
int			expand_find_dollar(const char *s); 
// NIEUW: Hoofdfunctie voor Expansie en de finale Quote Removal
// NIEUW: Helperfunctie die alle quotes uit een string verwijdert
char		*strip_all_quotes(char *original_str);
// Prototypes for string manipulation functions used across files
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_append_char(char *s, char c);

/*============================*/
/* PARSER           */
/*============================*/

int			parser_build_cmd(t_commando *cmd_list);
int			parse_pipeline(t_commando *cmd_list, t_ast *out);
void		parser_free_cmds(t_commando *cmd);
void		free_ast(t_ast *ast);
void		redir_set_pending(int *pending, t_token *tok);

// MISSING: Functions for splitting and building command structures
t_commando	*parser_split_pipes(t_token *tokens);
int			parser_build_redirs(t_commando *cmd_list);

// Prototype voor de functie die in parser_build_cmd.c wordt gebruikt (NIEUW):
int			build_redirs_for_one(t_commando *cmd); // <-- TOEGEVOEGD

/*============================*/
/* HEREDOC            */
/*============================*/

int			prepare_heredocs(t_ast *ast, t_env_entry *env, int last_status);

/*============================*/
/* BUILTINS           */
/*============================*/

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

/*============================*/
/* EXECUTOR          */
/*============================*/

char		*resolve_cmd_path(const char *cmd, t_env_entry *env);
char		**build_envp(t_env_entry *env);
void		free_envp(char **envp);
int			execute_simple_cmd(char **argv, t_env_entry *env);
int			execute_ast(t_ast *ast, t_env_entry **env, int *last_status);
int			apply_redirs(t_redir *redirs);
int			validate_redirs(t_redir *redirs);

// MISSING: Helper function for executing external commands in a child process
void		execute_external_cmd(t_command_data *cmd, t_env_entry **env_head);


/*============================*/
/* SIGNALS          */
/*============================*/

void		setup_prompt_signal_handlers(void);
int			shell_get_signal(void);
void		shell_set_signal(int sig);


/*============================*/
/* TERMINAL IO        */
/*============================*/

int			terminal_hide_control_chars(void);
int			terminal_restore_control_chars(void);
int	terminal_enable_control_chars(void);

/*============================*/
/* PROMPT           */
/*============================*/

// Both prototypes for reading the line
char		*read_prompt_line(void);
char		*read_prompt(const char *prompt);

#endif
