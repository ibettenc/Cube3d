/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:39:26 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/25 16:28:01 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	nb_len(long n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nb;
	size_t	len;

	nb = n;
	len = nb_len(nb);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nb < 0)
	{
		result [0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		result[0] = '0';
	while (nb > 0)
	{
		result[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (result);
}

/*
#include <stdio.h>
int	main()
{
	int n = -2147483648;
	char *res;
	res = ft_itoa(n);
	printf("%s\n", res);
	return 0;
}*/
