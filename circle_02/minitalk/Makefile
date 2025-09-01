# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwindey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/05 15:15:24 by gwindey           #+#    #+#              #
#    Updated: 2025/08/05 18:12:45 by gwindey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Targets
NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

# Default
all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

# Libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Mandatory
$(NAME_SERVER): server.c $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) server.c -L$(LIBFT_DIR) -lft

$(NAME_CLIENT): client.c $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) client.c -L$(LIBFT_DIR) -lft

# Bonus
$(NAME_SERVER_BONUS): server_bonus.c $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) server_bonus.c -L$(LIBFT_DIR) -lft

$(NAME_CLIENT_BONUS): client_bonus.c $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) client_bonus.c -L$(LIBFT_DIR) -lft

bonus: $(LIBFT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

# Clean
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all bonus clean fclean re
