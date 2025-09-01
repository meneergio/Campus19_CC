/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:43:16 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 17:06:07 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int	find_min_position(t_node *stack)
{
	int	min_index;
	int	position;
	int	min_pos;

	if (!stack)
		return (-1);
	min_index = stack->index;
	min_pos = 0;
	position = 0;
	while (stack)
	{
		if (stack->index < min_index)
		{
			min_index = stack->index;
			min_pos = position;
		}
		stack = stack->next;
		position++;
	}
	return (min_pos);
}

int	find_max_index(t_node *stack)
{
	int	max_index;

	if (!stack)
		return (-1);
	max_index = stack->index;
	while (stack)
	{
		if (stack->index > max_index)
			max_index = stack->index;
		stack = stack->next;
	}
	return (max_index);
}

int	find_position_by_index(t_node *stack, int target_index)
{
	int	position;

	position = 0;
	while (stack)
	{
		if (stack->index == target_index)
			return (position);
		stack = stack->next;
		position++;
	}
	return (-1);
}

int	find_max_position(t_node *stack)
{
	int	max_index;
	int	position;
	int	max_pos;

	if (!stack)
		return (-1);
	max_index = stack->index;
	max_pos = 0;
	position = 0;
	while (stack)
	{
		if (stack->index > max_index)
		{
			max_index = stack->index;
			max_pos = position;
		}
		stack = stack->next;
		position++;
	}
	return (max_pos);
}

int	is_in_range(int index, int min, int max)
{
	return (index >= min && index <= max);
}
