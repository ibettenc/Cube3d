/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:52:20 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/25 18:16:40 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	is_in_set(char c, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	char_count(char const *s1, char const *set)
{
	size_t	i;
	size_t	count;

	count = ft_strlen(s1);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
	{
		count -= 1;
		i++;
	}
	i = ft_strlen(s1);
	while (i > 0 && s1[i - 1] && is_in_set(s1[i - 1], set) && count > 0)
	{
		count -= 1;
		i--;
	}
	return (count);
}

char	*valid_char(char const *s1, char const *set, char *trimmed)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	start = i;
	i = ft_strlen(s1);
	while (s1[i - 1] && is_in_set(s1[i - 1], set))
		i--;
	end = i;
	i = 0;
	while (start + i < end)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		nb_char;

	if (!s1 || !set)
		return (NULL);
	nb_char = char_count(s1, set);
	trimmed = malloc((nb_char + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	trimmed = valid_char(s1, set, trimmed);
	return (trimmed);
}
/*
#include <stdio.h>
int	main()
{
	char const *bob = "";
	char const *non = "";
	char *result = ft_strtrim(bob, non);
	printf("%s", result);
	return 0;

}*/
