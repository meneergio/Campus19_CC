# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwindey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 14:18:40 by gwindey           #+#    #+#              #
#    Updated: 2025/05/29 15:28:13 by gwindey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f

SRCS =  ft_printf.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_puthex.c \
        ft_putunsigned.c \
        ft_putptr.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# Dit zorgt ervoor dat de objectbestanden worden gemaakt voordat de library wordt aangemaakt
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compileren van elke .c naar een .o bestand
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
