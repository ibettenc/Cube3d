/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:13:11 by raantoin          #+#    #+#             */
/*   Updated: 2026/04/30 17:23:59 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map =
	""

int	main(int argc, char **argv)
{
	if (check_arg(argc, argv) == 0)
		return (0);
}

int	check_arg(int argc, char **argv)
{
	int n;
	if (argc != 2)
	{
		printf("Incorrect number of arguments!\n");
		return (0);
	}
	n = ft_strlen(argv[1]);
	if ((n <= 4) || ft_strncmp(&argv[1][n - 4], ".cub", 4) != 0)
	{
		printf("Error, the file must be of format .cub\n");
		return (0);
	}
	return (1);
}

