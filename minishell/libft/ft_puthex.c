/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:08:48 by gwindey           #+#    #+#             */
/*   Updated: 2025/05/29 15:54:09 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, char format)
{
	char	*hex_lowercase;
	char	*hex_uppercase;
	int		len;

	len = 0;
	hex_lowercase = "0123456789abcdef";
	hex_uppercase = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_puthex(n / 16, format);
	if (format == 'x')
		len += ft_putchar(hex_lowercase[n % 16]);
	else
		len += ft_putchar(hex_uppercase[n % 16]);
	return (len);
}
/*
#include "ft_printf.h"

int main(void)
{
    ft_puthex(255, 'x');  // Should print: ff (lowercase)
    ft_puthex(255, 'X');  // Should print: FF (uppercase)
    return 0;
}
*/
