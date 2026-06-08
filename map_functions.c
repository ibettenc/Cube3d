/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 20:55:32 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/01 22:04:26 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_char_start(t_map_par *map_par)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_par->map[i][j])
		{
			if (map_par->map[i][j] == 'W' || map_par->map[i][j] == 'E' 
			|| map_par->map[i][j] == 'S' || map_par->map[i][j] == 'N')
			{
				map_par->char_pos[0] = i;
				map_par->char_pos[1] = j;
				break;
			}
			j++;
		}
		i++;
	}
}
