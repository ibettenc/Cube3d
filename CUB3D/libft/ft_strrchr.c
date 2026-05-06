/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:11:22 by raantoin          #+#    #+#             */
/*   Updated: 2025/04/26 12:30:17 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	i = ft_strlen(s);
	ch = (char) c;
	if (ch == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		if (s[i - 1] == ch)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main()
{
	char *chec = "allergiement";
	char *res;
	res = ft_strrchr(chec, 101);
	printf("%s", res);
	return 0;
}*/
