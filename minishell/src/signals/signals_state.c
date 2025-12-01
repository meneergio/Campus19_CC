/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:36:29 by dzotti            #+#    #+#             */
/*   Updated: 2025/09/24 14:36:29 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// opslag voor 'laatste ontvangen signaal'
static int	*signal_slot(void)
{
	static int	last_signal;

	return (&last_signal);
}

int	shell_get_signal(void)
{
	return (*signal_slot());
}

void	shell_set_signal(int sig)
{
	*signal_slot() = sig;
}
