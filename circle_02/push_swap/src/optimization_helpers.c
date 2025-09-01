/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:57:23 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 18:10:37 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdio.h>

int	get_chunk_size(int total_size)
{
	if (total_size <= 100)
		return (total_size / 5);
	else if (total_size <= 500)
		return (total_size / 8);
	else
		return (total_size / 16);
}

int	calculate_move_cost(t_node *stack, int target_index)
{
	int		position;
	int		size;
	t_node	*current;

	position = 0;
	size = stack_size(stack);
	current = stack;
	while (current && current->index != target_index)
	{
		current = current->next;
		position++;
	}
	if (!current)
		return (INT_MAX);
	if (position <= size / 2)
		return (position);
	else
		return (size - position);
}

int	find_most_efficient_element(t_node *stack, int min_range, int max_range)
{
	t_node	*current;
	int		position;
	int		best_pos;
	int		min_cost;
	int		cost;

	current = stack;
	position = 0;
	best_pos = -1;
	min_cost = INT_MAX;
	while (current)
	{
		if (is_in_range(current->index, min_range, max_range))
		{
			cost = calculate_move_cost(stack, current->index);
			if (cost < min_cost)
			{
				min_cost = cost;
				best_pos = position;
			}
		}
		current = current->next;
		position++;
	}
	return (best_pos);
}

int	count_elements_in_chunk(t_node *a, int min_range, int max_range)
{
	int		elements_in_chunk;
	t_node	*temp;

	elements_in_chunk = 0;
	temp = a;
	while (temp)
	{
		if (is_in_range(temp->index, min_range, max_range))
			elements_in_chunk++;
		temp = temp->next;
	}
	return (elements_in_chunk);
}
