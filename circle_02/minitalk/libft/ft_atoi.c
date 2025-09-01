/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:42:46 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/10 15:51:14 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char str[])
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
/*
#include <stdio.h>

int main()
{
    const char str1[] = "   -12345abc";
    const char str2[] = "42";
    const char str3[] = " \t\n  9876";
    const char str4[] = "+567";

    printf("Resultaat van ft_atoi(str1): %d\n", ft_atoi(str1));  // -12345
    printf("Resultaat van ft_atoi(str2): %d\n", ft_atoi(str2));  // 42
    printf("Resultaat van ft_atoi(str3): %d\n", ft_atoi(str3));  // 9876
    printf("Resultaat van ft_atoi(str4): %d\n", ft_atoi(str4));  // 567

    return 0;
}
*/
