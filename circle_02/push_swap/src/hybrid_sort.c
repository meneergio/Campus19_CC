/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hybrid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:58:26 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/10 12:01:05 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	hybrid_sort(t_node **a, t_node **b, int size)
{
	if (stack_is_sorted(*a))
		return ;
	if (size <= 1)
		return ;
	else if (size == 2)
	{
		if ((*a)->index > (*a)->next->index)
			sa(a);
	}
	else if (size <= 5)
		sort_five(a, b);
	else if (size <= 100)
		optimized_chunk_sort(a, b);
	else if (size <= 500)
		optimized_large_sort(a, b, size);
	else
		radix_sort(a, b);
}
