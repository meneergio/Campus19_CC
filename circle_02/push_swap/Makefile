# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwindey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/20 09:57:31 by gwindey           #+#    #+#              #
#    Updated: 2025/09/09 14:57:29 by gwindey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
LIBFT		= libft/libft.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iincludes -Ilibft
SRCS		= src/main.c src/parser.c src/sorting_algorithms.c \
			  src/operations.c src/stack_utils.c src/helper_functions.c \
			  src/optimization_helpers.c src/radix_sort.c src/error.c \
			  src/rotate.c src/reverse_rotate.c src/stack.c \
			  src/index_stack.c src/helper_functions_2.c \
			  src/optimization_large_sort.c src/push_back_optimized.c \
			  src/operations_2.c src/hybrid_sort.c \
			  src/sorting_algorithms_extra.c

OBJS		= $(SRCS:.c=.o)

# Kleuren voor logging
GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled$(NC)"

$(LIBFT):
	@echo "$(GREEN)🛠️  Compiling libft...$(NC)"
	@make -C libft
	@cp libft/libft.h includes/  # Kopieer header indien nodig

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C libft clean
	@echo "$(RED)🧹 Object files removed$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(RED)🧹 $(NAME) removed$(NC)"

re: fclean all

.PHONY: all clean fclean re
