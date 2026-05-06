/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:05:44 by raantoin          #+#    #+#             */
/*   Updated: 2025/05/06 16:59:40 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

unsigned int	ft_strcopy(char *dest, char const *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	size_t	total_len;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	concat = malloc((total_len + 1) * sizeof(char));
	if (!concat)
		return (NULL);
	j = 0;
	ft_strcopy(&concat[j], &s1[0]);
	j += ft_strlen(s1);
	ft_strcopy(&concat[j], &s2[0]);
	j += ft_strlen(s2);
	concat[j] = '\0';
	return (concat);
}

/*
#include <stdio.h>
int	main()
{
	char *s1 = "ASphaLTE";
	char *s2 = "Dormitorium";
	char *result = ft_strjoin(s1, s2);
	printf("%s", result);
	return 0;
}*/
