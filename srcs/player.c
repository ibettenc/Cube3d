/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.curr                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:15:14 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/04 19:02:50 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	char	curr;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			curr = game->map.grid[y][x];
			if (curr == 'N' || curr == 'S' || curr == 'E' || curr == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				set_player_direction(&game->player, curr);
				game->player.move_speed = 0.01;
				game->player.rot_speed = 0.01;
				return ;
			}
			x++;
		}
		y++;
	}
}
