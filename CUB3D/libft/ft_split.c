/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:30:26 by raantoin          #+#    #+#             */
/*   Updated: 2025/05/06 17:44:57 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	ft_strncpy(char *dest, char const *src, int len)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	string_nbr(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && (s[i] != c))
				i++;
		}
	}
	return (count);
}

void	free_array(char **array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**splitting(char **array, char const *s, char c, int str_count)
{
	int	i;
	int	ind;
	int	cst;

	i = 0;
	cst = 0;
	while (cst < str_count)
	{
		while (s[i] && s[i] == c)
			i++;
		ind = i;
		while (s[i] && s[i] != c)
			i++;
		array[cst] = malloc((i - ind + 1) * sizeof(char));
		if (!array[cst])
		{
			free_array(array, cst);
			return (NULL);
		}
		ft_strncpy(array[cst], &s[ind], i - ind);
		cst++;
	}
	array[cst] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		str_count;
	char	**array;
	char	**result;

	if (!s)
		return (NULL);
	str_count = string_nbr(s, c);
	array = malloc((str_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	result = splitting(array, s, c, str_count);
	return (result);
}
/*
#include <stdio.h>
int     main()
{
        char    *s = "ssarstatatiriontshafsssssttsetstuert";
        char 	c = 's';
        int i = 0;
        char **result = ft_split(s, c);
        while(result[i])
        {
                printf("%s\n", result[i]);
                free(result[i]);
                i++;
        }
        return 0;
}*/
