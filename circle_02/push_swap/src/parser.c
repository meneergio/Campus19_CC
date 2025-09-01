/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:15 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/20 10:25:47 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_duplicate(t_node *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	process_args(t_node **stack, char **args)
{
	long	val;
	int		i;

	i = 0;
	while (args[i])
	{
		if (!is_number(args[i]))
			error_exit(stack);
		val = ft_atol(args[i]);
		if (val < INT_MIN || val > INT_MAX || is_duplicate(*stack, val))
			error_exit(stack);
		stack_add_back(stack, new_node(val));
		i++;
	}
}

void	parse_input(t_node **stack, int argc, char **argv)
{
	char	**args;

	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args)
			error_exit(stack);
		process_args(stack, args);
		free_split(args);
	}
	else
		process_args(stack, argv + 1);
}
