/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:22:26 by ibettenc          #+#    #+#             */
/*   Updated: 2025/04/20 19:45:48 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*free_all(char **dst, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

char	*malloc_word(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	count_word(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**fill_malloc(char **dst, const char *s, char c)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	start = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			dst[j] = malloc_word(&s[start], i - start);
			if (!dst[j])
				return (free_all(dst, j));
			j++;
		}
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_split(const char *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!dst)
		return (NULL);
	return (fill_malloc(dst, s, c));
}
/*
#include <stdio.h>

int main(void)
{
	char **result;
	int i;

	result = ft_split("  blblblb c'est mon ventre  qui   gargouille   ", ' ');

	if (result)
	{
		i = 0;
		while (result[i])
		{
			printf("[%s]\n", result[i]);
			i++;
		}
		free_all(result, i);
	}
	else
	{
		printf("Erreur d'allocation mémoire\n");
	}

	return 0;
}*/
