/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raantoin <raantoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:19:22 by raantoin          #+#    #+#             */
/*   Updated: 2026/04/28 17:37:41 by raantoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_map_par
{
	int 	init_pos[2];
	char 	**map;
	void	*img;
	int		line_len;
	int		line_nb;
	int		size_x;
	int		size_y;
	char	*title;
	void	*exit;
	void	*mlx;
	void	*win;
	int		col_nb;
	int		fd_col;
	int		char_found;
	int		char_x;
	int		char_y;
	t_graph	graph;
}	t_map_par;

typedef struct s_graph
{
	void	*wall_east;
	void	*wall_west;
	void	*wall_south;
	void	*wall_north;
	void	*cha;
	
	
}	t_graph;

#endif