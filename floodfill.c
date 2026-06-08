/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 23:53:00 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/01 21:43:11 by raantoin         ###   ########.fr       */
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

int	accessible(t_map_par *map_par)
{
	int		*start_pos;
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map_par->char_pos = find_char_start(map_par);
	map_copy = copy_map(map_par);
	if (!map_copy)
		return (0);
	map_par->fd_col = 0;
	map_par->char_found = 0;
	while (map_copy[i][j])
	{
		
	}
	flood_fill(map_copy, map_par->char_pos[0], map_par->char_pos[1], map_par);
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

char	**uniform_map(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_par->map[i][j])
		{
			if (map_par->map[i][j] == '0' || map_par->map[i][j] == 'W'
			|| map_par->map[i][j] == 'E' || map_par->map[i][j] == 'S'
			|| map_par->map[i][j] == 'N')
				map_copy[i][j] = '0';
			j++;
		}
		i++;
	}
	return copy_map;
}

void	flood_fill(char **map_copy, int i, int j, t_map_par *map_par)
{
	if (i < 0 || j < 0 || map_copy[i][j] == '1')
		return ;
	if (i >= map_par->line_nb || j >= map_par->line_len)
		return ;
	if (map_copy[i][j] == ' ')
		return ;
	map_copy[i][j] = '2';
	flood_fill(map_copy, i + 1, j, map_par);
	flood_fill(map_copy, i - 1, j, map_par);
	flood_fill(map_copy, i, j + 1, map_par);
	flood_fill(map_copy, i, j - 1, map_par);
}

void	all_flood(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	rectangularize(map_par);
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_copy[i][j])
		{
			if (map_copy[i][j] == '0')
				flood_fill(map_copy, i , j, map_par);
			j++;
		}
		i++;
	}
	valid_char(map_par, map_copy);
}

int	valid_char(t_map_par *map_par, char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_par->line_nb)
	{
		j = 0;
		while (j < map_par->line_len && map_copy[i][j])
		{
			if (map_copy[i][j] != '2' && map_copy[i][j] != '1'
				&& map_copy[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**copy_rectangularize(t_map_par *map_par)
{
	int		i;
	int		j;
	int		len;
	char	**map_copy;

	i = 0;
	map_copy = copy_map(map_par);
	while (i < map_par->line_nb)
	{
		len = ft_strlen(map_par->map[i]);
		j = len;
		while (j < map_par->line_len)
		{
			map_par->map[i][j] = ' ';
			j++;
		}
		map_par->map[i][j] = '\0';
		i++;
	}
	return map_copy;
}

void	find_map_cub(int fd)
{
	
}

// ignorer tous les espaces avant les chiffres et ceux entres
// verifier pour tous les '2' qu'ils soient bien isoles du reste.
// s'assurer que les 1 soient colles au reste de la carte