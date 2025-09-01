/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:03:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/05/29 15:56:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdint.h>
#include <unistd.h>

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
		return (ft_putstr("(nil)"));
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
