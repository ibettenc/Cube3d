/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:42:41 by ibettenc          #+#    #+#             */
/*   Updated: 2025/06/02 15:08:51 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// args = the list i want to fill
// format = last param known before "..."

int	putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	putstr(char *str)
{
	int	i;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	putnbr(int n)
{
	int		count;
	char	c;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count += putnbr(n / 10);
	}
	c = (n % 10) + '0';
	write(1, &c, 1);
	count++;
	return (count);
}

int	convert(va_list args, char c)
{
	if (c == 'c')
		return (putchar(va_arg(args, int)));
	else if (c == 's')
		return (putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (putchar('%'));
	else if (c == ' ')
		return (1);
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			i = convert(args, *(format + 1));
			if (i == -1)
				return (-1);
			count += i;
			format += 2;
		}
		else
		{
			putchar(*format++);
			count++;
		}
	}
	va_end(args);
	return (count);
}

/*#include <stdio.h>
int main()
{
	int	i = 10;
	// char *s = "bibi";
	int j = ft_printf("salut je suis %%%d", i);
	printf("\n");
	int k = printf("salut je suis %%%d", i);
	 if (j != k)
	 	printf("\nERROR\nj = %d et k = %d", j, k);
	 if (j == k)
	 	printf("\nOK\nj = %d et k = %d", j, k);
	return (0);
}*/