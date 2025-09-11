/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:07:00 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/10 12:00:28 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static int	calculate_distance(int position, int size)
{
	if (position <= size / 2)
		return (position);
	else
		return (size - position);
}

int	find_closest_in_range(t_node *stack, int min, int max)
{
	t_node	*current;
	int		position;
	int		closest_pos;
	int		min_distance;

	current = stack;
	position = 0;
	closest_pos = -1;
	min_distance = INT_MAX;
	while (current)
	{
		if (is_in_range(current->index, min, max))
		{
			if (calculate_distance(position, stack_size(stack)) < min_distance)
			{
				min_distance = calculate_distance(position, stack_size(stack));
				closest_pos = position;
			}
		}
		current = current->next;
		position++;
	}
	return (closest_pos);
}

static void	rotate_forward(t_node **stack, int target_pos, char stack_name)
{
	while (target_pos-- > 0)
	{
		if (stack_name == 'a')
			ra(stack);
		else
			rb(stack);
	}
}

static void	rotate_backward(t_node **stack, int target_pos, char stack_name)
{
	while (target_pos-- > 0)
	{
		if (stack_name == 'a')
			rra(stack);
		else
			rrb(stack);
	}
}

void	rotate_to_position(t_node **stack, int target_pos, char stack_name)
{
	int	size;

	size = stack_size(*stack);
	if (target_pos < 0)
		return ;
	if (target_pos == 0)
		return ;
	if (target_pos <= size / 2)
		rotate_forward(stack, target_pos, stack_name);
	else
	{
		target_pos = size - target_pos;
		rotate_backward(stack, target_pos, stack_name);
	}
}
