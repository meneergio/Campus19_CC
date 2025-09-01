/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hybrid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:58:26 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/01 13:32:45 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	hybrid_sort(t_node **a, t_node **b, int size)
{
	if (stack_is_sorted(*a))
		return ;
	if (size <= 5)
		sort_five(a, b);
	else if (size <= 100)
		optimized_chunk_sort(a, b);
	else if (size <= 500)
		optimized_large_sort(a, b, size);
	else
		radix_sort(a, b);
}
