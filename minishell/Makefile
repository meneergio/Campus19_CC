NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -Iinclude

READLINE_INC ?= /opt/homebrew/opt/readline/include
READLINE_LIB ?= /opt/homebrew/opt/readline/lib

CFLAGS += -I$(READLINE_INC)
LDFLAGS := -L$(READLINE_LIB) -lreadline

LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a
CFLAGS += -I$(LIBFT_DIR)

SRC := \
	src/main/main.c \
	src/main/line_process.c \
	src/main/buffer_process.c \
	src/terminal/prompt_basic.c \
	src/terminal/terminal_control.c \
	src/signals/signals_prompt.c \
	src/signals/signals_state.c \
	src/env/env_node.c \
	src/env/env_list.c \
	src/env/env_load.c \
	src/env/env_shlvl.c \
	src/lexer/lexer_core.c \
	src/lexer/lexer_tokens.c \
	src/lexer/lexer_redir.c \
	src/lexer/lexer_quote.c \
	src/lexer/lexer_word.c \
	src/expand/expand_utils.c \
	src/expand/expand_simple.c \
	src/expand/expand_word.c \
	src/expand/expand_line_utils.c \
	src/expand/expand_read_name.c \
	src/parser/parser_split.c \
	src/parser/parser_free_cmds.c \
	src/parser/parser_build_cmd.c \
	src/parser/parser_build_redirs.c \
	src/parser/parser_utils.c \
	src/parser/parser_free_ast.c \
	src/parser/parser_debug.c \
	src/parser/parse_pipeline.c \
	src/parser/parser_redir_utils.c \
	src/parser/parser_pipe_utils.c \
	src/heredoc/heredoc_prepare.c \
	src/heredoc/heredoc_input.c \
	src/heredoc/heredoc_utils.c \
	src/builtins/builtin_pwd.c \
	src/builtins/builtin_cd.c \
	src/builtins/builtin_echo.c \
	src/builtins/builtin_env.c \
	src/builtins/builtin_exit.c \
	src/builtins/builtin_utils.c \
	src/builtins/builtin_export.c \
	src/builtins/builtin_export_sort.c \
	src/builtins/builtin_unset.c \
	src/builtins/builtin_export_assignment.c \
	src/exec/path_resolve.c \
	src/exec/env_build.c \
	src/exec/execute_simple.c \
	src/exec/execute_status.c \
	src/exec/execute_external.c \
	src/exec/execute_single.c \
	src/exec/execute_single_utils.c \
	src/exec/execute_pipeline_utils.c \
	src/exec/execute_pipeline.c \
	src/exec/execute_ast.c \
	src/exec/redirections.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT_A) -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
