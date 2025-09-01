/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithms.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:32:32 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 14:56:54 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_node **stack_a)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
	{
		if ((*stack_a)->next->index < (*stack_a)->next->next->index
			&& (*stack_a)->index < (*stack_a)->next->next->index)
			sa(stack_a);
		else if ((*stack_a)->next->next->index < (*stack_a)->next->index)
		{
			sa(stack_a);
			rra(stack_a);
		}
		else
			ra(stack_a);
	}
	else if ((*stack_a)->next->next->index < (*stack_a)->index)
		rra(stack_a);
	else if ((*stack_a)->next->index > (*stack_a)->next->next->index)
	{
		rra(stack_a);
		sa(stack_a);
	}
}

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

void	sort_five(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
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
