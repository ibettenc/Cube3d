/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:24:58 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/25 15:00:00 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s)+1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>

char	to_upper(unsigned int i, char c) 
{
	i = i * 1;
	if (c >= 'a' && c <= 'z')
        	return c - 32;
	return c;
}

int main() 
{
	char *original = "Vercingetorix aurait DU gagner!";
	char *result = ft_strmapi(original, to_upper);
	if (result)
	{
		printf("Result: %s\n", result);
		free(result);
	}
	else
		printf("Allocation failed.\n");
	return 0;
}*/
