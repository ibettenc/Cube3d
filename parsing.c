/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:57:15 by raantoin          #+#    #+#             */
/*   Updated: 2026/06/08 19:59:11 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parser(char *full_file, t_map_par *map_par)
{
	char	**file_text;
	char	*buffer;
	int		file_fd;
	int		i;
	
	i = 0;
	file_text = NULL;
	file_fd = open(full_file, O_RDONLY);
	buffer = get_next_line(file_fd);
	while (buffer != NULL)
	{
		file_text[i] = buffer;
		i++;
		buffer = get_next_line(file_fd);
	}
	file_text[i] = '\0';
	 if (file_sorter(file_text, map_par) == 0)
		return (NULL); // dans main.c, si fichier == NULL, exit le programme
	return (file_text);
}

int	skip_spaces(int j, char *line)
{
	while (line[j] == ' ')
		j++;
	return (j);
}

int	file_sorter(char **file, t_map_par *map_par) //decompose le fichier en morceaux
{
	int	i;
	int j;

	i = 0;
	if (check_dup(file, map_par) == 0)
		return (0);
	while (file[i])
	{
		j = 0;
		j = skip_spaces(j, file[i]);
		if (sorter_colour(file, i, j, map_par) == 0 
		|| sorter_walls(file, i, j, map_par) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	sorter_walls(char **file, int i, int j, t_map_par *map_par)
{
		int	ret;

		ret = 1;
		if (file[i][j] == 'W' && file[i][j + 1] == 'E')
			ret *= (check_text(&file[i][j + 2], "WE", map_par));
		if (file[i][j] == 'E' && file[i][j + 1] == 'A')
			ret *= (check_text(&file[i][j + 2], "EA", map_par));
		if (file[i][j] == 'N' && file[i][j + 1] == 'O')
			ret *= (check_text(&file[i][j + 2], "NO", map_par));
		if (file[i][j] == 'S' && file[i][j + 1] == 'O')
			ret *= (check_text(&file[i][j + 2], "SO", map_par));
		if (ret == 0)
		{
			printf("Error\n the file doesn't exist or you don't have access to it.\n");
			return (0);
		}
}

int	sorter_colour(char **file, int i, int j, t_map_par *map_par)
{
		if (file[i][j] == 'F')
		{
			j++;
			j = skip_spaces(j, file[i]);
			if (valid_colours(&file[i][j]))
				map_par->floor = &file[i][j];
			else
				return (0);
		}
		if (file[i][j] == 'C')
		{
			j++;
			j = skip_spaces(j, file[i]);
			if (valid_colours(&file[i][j]))
				map_par->ceiling = &file[i][j];
			else
				return (0);
		}
		return (1);
}

int	file_sort_walls(char *wall, t_map_par *map_par)//enlever?
{
	int		i;
	
	i = 0;
	if (wall[i] == 'W' && wall[i + 1] == 'E')
	{
		while (wall[i])
		{
			i = skip_spaces(i, &wall[i]);
			if (is_accessible(&wall[i]))
				map_par->west_wall = &wall[i];
		}
	}
	if (wall[i] == 'E' && wall[i + 1] == 'A')
	if (wall[i] == 'N' && wall[i + 1] == 'O')
	if (wall[i] == 'S' && wall[i + 1] == 'O')
}

//savoir passer par des lignes vides et recuperer les infos malgre l'ordre
//  Except for the map, each type of information from an element can be separated by one or more spaces.
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

int	valid_map()
{
	
}

// recuperer les donnees du fichier 

/*
remplir la map pour en faire un carre avant de lancer les tests? et faire de ces cases des espaces ?
maps invalides:
- si pas tout est ferme, on return message erreur. Pour verifier, on fait un floodfill dans une map copiee qui se lance dans chaque position(i, j) == '0' et
  Verifier les coins aussi.
Tout ce qui precede la map peut etre separe par des lignes vides.
Except for the map content which always has to be the last, each type of element can be set in any order in the file.
 If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.
*/
