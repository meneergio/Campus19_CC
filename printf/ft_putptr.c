/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:03:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/25 15:51:44 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h> // for uintptr_t

static int	print_ptr_hex(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr >= 16)
		len += print_ptr_hex(ptr / 16);
	len += ft_putchar("0123456789abcdef"[ptr % 16]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		len += ft_putstr("(nil)");
		return (len);
	}
	len += ft_putstr("0x");
	len += print_ptr_hex((uintptr_t)ptr);
	return (len);
}
/*
#include "ft_printf.h"

int main(void)
{
    void *ptr = (void *)0x7fff1f6e4a00;
    ft_putptr(ptr);  // Should print: 7fff1f6e4a00
    return 0;
}
*/
