/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:05 by ibettenc          #+#    #+#             */
/*   Updated: 2025/05/21 17:46:10 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n)
{
	int		count;
	char	nbr;

	count = 0;
	if (n > 9)
	{
		count += ft_putunsigned(n / 10);
		nbr = (n % 10) + '0';
		write(1, &nbr, 1);
		count++;
	}
	else
	{
		nbr = n + '0';
		write(1, &nbr, 1);
		count++;
	}
	return (count);
}

int	ft_puthexa(unsigned int j, char c)
{
	int		count;
	int		i;
	char	*hex_tab;
	char	dst[32];

	if (!j)
	{
		write(1, "0", 1);
		return (1);
	}
	if (c == 'x')
		hex_tab = "0123456789abcdef";
	else if (c == 'X')
		hex_tab = "0123456789ABCDEF";
	i = 0;
	while (j)
	{
		dst[i] = hex_tab[j % 16];
		j /= 16;
		i++;
	}
	count = i;
	while (--i >= 0)
		write(1, &dst[i], 1);
	return (count);
}

int	ft_putptr(void *p)
{
	uintptr_t	ptr;
	char		*hex;
	char		hex_str[32];
	int			i;
	int			count;

	hex = "0123456789abcdef";
	ptr = (uintptr_t)p;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	i = 0;
	write(1, "0x", 2);
	while (ptr != 0)
	{
		hex_str[i] = hex[ptr % 16];
		ptr /= 16;
		i++;
	}
	count = i + 2;
	while (--i >= 0)
		write(1, &hex_str[i], 1);
	return (count);
}

//uintptr_t is big enough to contain a pointeur, int ou unsigned are too small
//last line write an invert tab bc we got it in reverse
/*
int main()
{
        void    *p = "";
        ft_putptr(p);
        printf("\nresultat du printf: %p", p);
        return 0;
}

#include <stdio.h>
int main()
{
        unsigned int j = 2000;
	char c = 'x';
    //	char c = 'X';
        ft_puthexa(j, c);
        printf("\nresultat du printf: %x", j);
    //	printf("\nresultat du printf: %X", j);
        return 0;
}

int main()
{
	unsigned int n = 42;
	ft_putunsigned(n);
	printf("\nresultat du printf: %d", n);
}*/