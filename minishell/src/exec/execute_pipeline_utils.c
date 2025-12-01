/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:55:35 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/27 15:40:48 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Sluit alle pipe-ends in een pipe-array
void	close_all_pipes(int count, int (*pipes)[2])
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

// Wacht op reeds gespawnde children (bij fout in fork)
void	wait_spawned_children(int spawned, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < spawned)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

// Vrijt pipe- en pid-arrays en geeft 1 terug (voor error paths)
int	free_pipe_data(int (*pipes)[2], pid_t *pids)
{
	free(pipes);
	free(pids);
	return (1);
}
