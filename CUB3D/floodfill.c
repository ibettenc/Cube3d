/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:53:00 by raantoin          #+#    #+#             */
/*   Updated: 2026/05/06 15:20:18 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_map_par *map_par)
{
	int		i;
	char	**copy;

	i = 0;
	while (map_par->map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map_par->map[i])
	{
		copy[i] = ft_strdup(map_par->map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(char **map_copy, int i, int j, t_map_par *map_par)
{
	if (i < 0 || map_copy[i][j] == '1')
		return ;
	map_copy[i][j] = 'F';
	flood_fill(map_copy, i + 1, j, map_par);
	flood_fill(map_copy, i - 1, j, map_par);
	flood_fill(map_copy, i, j + 1, map_par);
	flood_fill(map_copy, i, j - 1, map_par);
}

void	flood_fill(t_map_par *map, int x, int y)
{
	if (y < 0 || y >= map->hit)
		return ;
	if (x < 0 || x >= (int) ft_strlen(map->map[y]))
		return ;
	if (map->map[y][x] != ' ')
		return ;
	map->map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	accessible(t_map_par *map_par)
{
	int		*start_pos;
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	start_pos = find_char_start(map_par);
	map_par->char_x = start_pos[1];
	map_par->char_y = start_pos[0];
	map_copy = copy_map(map_par);
	if (!map_copy)
		return (0);
	map_par->fd_col = 0;
	map_par->char_found = 0;
	while (map_copy[i][j])
	{
		
	}
	flood_fill(map_copy, map_par->char_y, map_par->char_x, map_par);
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	free(start_pos);
	if (map_par->fd_col == map_par->col_nb && map_par->char_found)
		return (1);
	write(1, "Error, elements are not reachable\n", 35);
	return (0);
}

char	**square_map(t_map_par *map_par, char **copy_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len)
		{
			if (map_par->map[i][j] == '0' || map_par->map[i][j] == 'W'
			|| map_par->map[i][j] == 'E' || map_par->map[i][j] == 'S'
			|| map_par->map[i][j] == 'N')
				copy_map[i][j] == '2';
			j++;
		}
		i++;
	}
	return copy_map;
}

void	find_map_cub(int fd)
{
	
}
