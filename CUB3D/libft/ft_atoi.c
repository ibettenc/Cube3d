/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:33:22 by raantoin          #+#    #+#             */
/*   Updated: 2025/05/12 13:06:47 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <limits.h>

int	over_long(unsigned long result, int sign)
{
	if (result > LONG_MAX && sign == 1)
		return (1);
	else if (result > LONG_MAX && sign == -1)
		return (0);
	return (result);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	if (str[i] == 45 || str[i] == 43)
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (over_long(result, sign) * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char *str = "-085";
	int res;
	int res1;
	res = ft_atoi(str);
	res1 = atoi(str);
	printf("%d\n", res);
	printf("%d\n", res1);
	return (0);
}*/
