/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_large_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:57:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 17:57:23 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	finalize_stack_a(t_node **a)
{
	if (stack_size(*a) == 3)
		sort_three(a);
	else if (stack_size(*a) == 2 && (*a)->index > (*a)->next->index)
		sa(a);
}

static void	process_chunk(t_node **a, t_node **b, int min_range, int max_range)
{
	int	elements_in_chunk;
	int	best_pos;
	int	mid_point;

	elements_in_chunk = count_elements_in_chunk(*a, min_range, max_range);
	while (elements_in_chunk > 0 && stack_size(*a) > 3)
	{
		best_pos = find_most_efficient_element(*a, min_range, max_range);
		if (best_pos == -1)
			break ;
		rotate_to_position(a, best_pos, 'a');
		pb(a, b);
		elements_in_chunk--;
		if (*b && (*b)->next && stack_size(*b) > 1)
		{
			mid_point = (min_range + max_range) / 2;
			if ((*b)->index <= mid_point)
				rb(b);
		}
	}
}

void	optimized_large_sort(t_node **a, t_node **b, int size)
{
	int	chunk_size;
	int	chunks;
	int	i;
	int	min_range;
	int	max_range;

	chunk_size = get_chunk_size(size);
	chunks = (size + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < chunks)
	{
		min_range = i * chunk_size;
		max_range = (i + 1) * chunk_size - 1;
		if (max_range >= size)
			max_range = size - 1;
		process_chunk(a, b, min_range, max_range);
		i++;
	}
	finalize_stack_a(a);
	push_back_optimized(a, b);
}

void	optimized_chunk_sort(t_node **a, t_node **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 3)
	{
		sort_three(a);
		return ;
	}
	else if (size <= 5)
	{
		sort_five(a, b);
		return ;
	}
	optimized_large_sort(a, b, size);
}
