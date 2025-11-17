/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:26:26 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/13 14:17:33 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// orginele inst. bewaren en later herstellen
static int	termios_slot(struct termios *set, int write_mode)
{
	static struct termios	saved;
	static int				has_saved;

	if (write_mode)
	{
		saved = *set;
		has_saved = 1;
		return (0);
	}
	if (has_saved)
		return (tcsetattr(STDIN_FILENO, TCSANOW, &saved));
	return (0);
}

// verberg cntrl 'C' '\' door ECHOTL uit te zetten
int	terminal_hide_control_chars(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (-1);
	termios_slot(&t, 1);
	t.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
		return (-1);
	return (0);
}

// zet orginele terug
int	terminal_restore_control_chars(void)
{
	return (termios_slot(NULL, 0));
}

// Zet ECHOCTL expliciet aan (voor child processen)
int	terminal_enable_control_chars(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return (-1);
	t.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
		return (-1);
	return (0);
}
