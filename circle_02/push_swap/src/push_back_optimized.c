/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_optimized.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:12:39 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 17:12:56 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_back_optimized(t_node **a, t_node **b)
{
	int	max_index;
	int	max_pos;

	while (*b)
	{
		max_index = find_max_index(*b);
		max_pos = find_position_by_index(*b, max_index);
		if (max_pos <= stack_size(*b) / 2)
		{
			while (max_pos-- > 0)
				rb(b);
		}
		else
		{
			max_pos = stack_size(*b) - max_pos;
			while (max_pos-- > 0)
				rrb(b);
		}
		pa(a, b);
	}
}
