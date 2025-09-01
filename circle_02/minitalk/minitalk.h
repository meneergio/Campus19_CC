/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:35:23 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/12 10:24:44 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <errno.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_server_data
{
	char	received_char;
	int		bit_count;
	pid_t	client_pid;
}	t_server_data;

#endif
