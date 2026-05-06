/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:29:09 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/17 15:36:22 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = ((unsigned char *)s);
	i = 0;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>
int	main()
{
	char s[] = "goucantarixe";
	int c = 99;
	size_t n = 4;
	void *res = ft_memset(s, c, n);
	printf("%s\n", (char *)res);
	return 0;
}*/
