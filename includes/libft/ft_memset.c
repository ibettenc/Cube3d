/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:06:29 by ibettenc          #+#    #+#             */
/*   Updated: 2025/04/11 16:01:39 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pif;

	pif = (unsigned char *) b;
	while (len > 0)
	{
		*pif = (unsigned char) c;
		pif++;
		len--;
	}
	return (b);
}
