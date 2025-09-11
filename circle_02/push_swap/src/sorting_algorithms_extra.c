/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithms_extra.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:52:45 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/09 14:56:04 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_min_to_b(t_node **stack_a, t_node **stack_b)
{
	int	min_pos;
	int	size;

	min_pos = find_min_position(*stack_a);
	size = stack_size(*stack_a);
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(stack_a);
	}
	else
	{
		min_pos = size - min_pos;
		while (min_pos-- > 0)
			rra(stack_a);
	}
	pb(stack_a, stack_b);
}

static void	finalize_sort_five(t_node **stack_a, t_node **stack_b, int size)
{
	if (size == 3)
		sort_three(stack_a);
	else if (size == 2 && (*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}

void	sort_five(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	finalize_sort_five(stack_a, stack_b, size);
}

void	chunk_sort(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	if (size <= 5)
		sort_five(stack_a, stack_b);
	else if (size <= 50)
		optimized_chunk_sort(stack_a, stack_b);
	else if (size <= 100)
		optimized_chunk_sort(stack_a, stack_b);
	else
		optimized_chunk_sort(stack_a, stack_b);
}
