/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:59:15 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/15 19:55:41 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_memory(char **file, t_map_par *map_par)
{
	char	**map;
	int		i;
	int		j;

	i = map_par->last_info_ln;
	while (empty_line(file[i]))
		i++;
	j = 0;
	while (file[i])
	{
		map[j] = file[i + j];
		j++;
	}
	map_par->map = map;
}

int	empty_line(char *file)
{
	int i;
	
	i = 0;
	while (file[i])
	{
		if (file[i] == ' ' || file[i] == '\t' || file[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}
