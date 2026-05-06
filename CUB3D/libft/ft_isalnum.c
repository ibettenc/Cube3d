/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:04:29 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/22 19:24:55 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (c <= 47 || c > 122 || (c > 57 && c < 65) || (c > 90 && c < 97))
		return (0);
	return (1);
}

/*
#include <stdio.h>
int	main()
{
	int h = 51;
	int res;
	res = ft_isalnum(h);
	printf("%d", res);
	return 0;
}*/
