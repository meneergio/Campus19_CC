# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwindey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/01 16:34:57 by gwindey           #+#    #+#              #
#    Updated: 2025/08/04 17:55:06 by gwindey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRCDIR = src
INCDIR = includes
MAPDIR = maps

# MiniLibX
MLX_DIR = ./minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files
SOURCES = main.c game_init.c game_logic.c key_handler.c \
          graphics.c render.c map_parser.c map_parser2.c \
          map_validation.c map_validate.c utils.c utils2.c \
		  map_validation_utils.c map_reader.c

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(SRCS:.c=.o)

# Header files
INCLUDES = -I$(INCDIR) $(MLX_INC)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Build rules
all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "$(GREEN)Building MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if they don't exist
$(SRCDIR):
	@mkdir -p $(SRCDIR)

$(INCDIR):
	@mkdir -p $(INCDIR)

$(MAPDIR):
	@mkdir -p $(MAPDIR)

# Utility rules
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

# Test rules
test: $(NAME)
	@echo "$(GREEN)Testing with maze.ber...$(RESET)"
	@./$(NAME) $(MAPDIR)/maze.ber

# Setup project structure
setup: $(SRCDIR) $(INCDIR) $(MAPDIR)
	@echo "$(GREEN)Project structure created!$(RESET)"

.PHONY: all clean fclean re test setup
