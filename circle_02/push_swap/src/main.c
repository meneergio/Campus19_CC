/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:18:23 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/23 16:11:59 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdio.h>

static void	choose_sorting_algorithm(t_node **stack_a,
										t_node **stack_b, int size)
{
	hybrid_sort(stack_a, stack_b, size);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		size;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (1);
	parse_input(&stack_a, argc, argv);
	if (stack_is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	index_stack(stack_a);
	size = stack_size(stack_a);
	choose_sorting_algorithm(&stack_a, &stack_b, size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
