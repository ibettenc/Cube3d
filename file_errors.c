/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:15:46 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/08 17:24:57 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_colours(char *colour)
{
	int		i;
	int		nb;
	int		nb_count;
	char	**numbers;

	i = 0;
	nb_count = 0;
	numbers = ft_split(colour, ',');
	while (numbers[i])
	{
		nb = ft_atoi(numbers[i]);
		if (nb < 0 || nb > 255)
		{
			printf("Error\n invalid colour values");
			return (0);
		}
		i++;
	}
	if (nb_count == 3)
		return (1);
	printf("Error\n invalid colour values");
	return (0);
}

int	check_dup(char **file, t_map_par *map_par)
{
	int	i;
	int	j;
	int	count[6];
	
	i = 0;
	while (i < 6)
		count[i++] = 0;
	i = 0;
	while (file[i])
	{
		j = 0;
		check_dup_helper(count, i, j, file, map_par);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (count[i] != 1)
		{
			printf("Error\n the file has missing or duplicate values!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_dup_helper(int *count, int i, int j, char **file, t_map_par *map_par)
{
	j = skip_spaces(j, file[i]);
	if (file[i][j] == 'F')
			count[0]++;
	if (file[i][j] == 'C')
		count[1]++;
	if (file[i][j] == 'W' && file[i][j + 1] == 'E')
		count[2]++;
	if (file[i][j] == 'E' && file[i][j + 1] == 'A')
		count[3]++;
	if (file[i][j] == 'N' && file[i][j + 1] == 'O')
		count[4]++;
	if (file[i][j] == 'S' && file[i][j + 1] == 'O')
		count[5]++;
}

int	check_text(char *path, char *direction, t_map_par *map_par)
{
	char	*new_path;
	int		spot;
	int		fd;

	spot = skip_spaces(0, path);
	new_path = &path[spot];
	fd = open(new_path, O_RDONLY);
	if (fd == - 1)
		return (0);
	close(fd);
	if (ft_strcmp(direction, "NO") == 0)
		map_par->texture_paths[0] = new_path;
	if (ft_strcmp(direction, "SO") == 0)
		map_par->texture_paths[1] = new_path;
	if (ft_strcmp(direction, "EA") == 0)
		map_par->texture_paths[2] = new_path;
	if (ft_strcmp(direction, "WE") == 0)
		map_par->texture_paths[3] = new_path;
	return (1);
}
