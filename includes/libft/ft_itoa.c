/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:58:59 by ibettenc          #+#    #+#             */
/*   Updated: 2025/04/15 18:56:14 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	long	nb;
	char	*s;

	nb = n;
	len = count_digits(nb);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	i = len - 1;
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		s[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (s);
}
