/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithms.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:32:32 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/09 14:55:39 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_node **stack_a)
{
	if ((*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a);
}

static void	sort_three_part(t_node **stack_a)
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

void	sort_three(t_node **stack_a)
{
	if (!*stack_a || !(*stack_a)->next)
		return ;
	if (!(*stack_a)->next->next)
	{
		sort_two(stack_a);
		return ;
	}
	sort_three_part(stack_a);
}
