/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:16:33 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/23 19:19:40 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t		len_src;
	char		*new_src;	

	len_src = ft_strlen(src);
	new_src = (char *)malloc((len_src + 1) * sizeof(char));
	if (!new_src)
	{
		return (NULL);
	}
	ft_strcpy(new_src, src);
	return (new_src);
}
/*
#include <stdio.h>
int	main()
{
	char *src = "Jeanry";
	char *result = ft_strdup(src);
	int i = 0;
	while(result[i])
	{
		printf("%c", result[i]);
		i++;
	}
	return 0;

}
*/
