/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:19:06 by ibettenc          #+#    #+#             */
/*   Updated: 2025/11/11 17:44:45 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_str(char *dst, const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t		len;
	char		*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(len);
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	copy_str(dst, s1);
	copy_str(dst + ft_strlen(s1), s2);
	free(s1);
	return (dst);
}

void	free_stash(char **stash)
{
	if (!stash || !*stash)
		return ;
	free(*stash);
	*stash = NULL;
}
