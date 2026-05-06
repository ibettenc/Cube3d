/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:20:57 by raantoin          #+#    #+#             */
/*   Updated: 2025/05/05 17:22:09 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_node;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current_node = *lst;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new;
	}
}
