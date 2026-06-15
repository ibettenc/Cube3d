/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:55:44 by ivan              #+#    #+#             */
/*   Updated: 2026/06/15 16:29:11 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_forward(t_game *game, double dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * game->player.move_speed * dir;
	new_y = game->player.y + game->player.dir_y * game->player.move_speed * dir;
	if (game->map.grid[(int)game->player.y][(int)(new_x + WALL_OFFSET)] != '1'
			&& game->map.grid[(int)game->player.y]
				[(int)(new_x - WALL_OFFSET)] != '1')
		game->player.x = new_x;
	if (game->map.grid[(int)(new_y + WALL_OFFSET)][(int)(new_x)] != '1'
			&& game->map.grid[(int)(new_y - WALL_OFFSET)][(int)(new_x)] != '1')
		game->player.y = new_y;
}

static void	move_strafe(t_game *game, double dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + (-game->player.dir_y)
		* game->player.move_speed * dir;
	new_y = game->player.y + game->player.dir_x
		* game->player.move_speed * dir;
	if (game->map.grid[(int)game->player.y][(int)(new_x + WALL_OFFSET)] != '1'
			&& game->map.grid[(int)game->player.y]
				[(int)(new_x - WALL_OFFSET)] != '1')
		game->player.x = new_x;
	if (game->map.grid[(int)(new_y + WALL_OFFSET)][(int)(new_x)] != '1'
			&& game->map.grid[(int)(new_y - WALL_OFFSET)]
				[(int)(new_x)] != '1')
		game->player.y = new_y;
}

static void	push_back(t_game *game)
{
	double	frac_x;
	double	frac_y;
	int		x;
	int		y;

	x = (int)game->player.x;
	y = (int)game->player.y;
	frac_x = game->player.x - floor(game->player.x);
	frac_y = game->player.y - floor(game->player.y);
	if (frac_x < 0.2 && game->map.grid[y][x - 1] == '1')
		game->player.x = floor(game->player.x) + 0.2;
	if (frac_x > 0.8 && game->map.grid[y][x + 1] == '1')
		game->player.x = floor(game->player.x) + 0.8;
	if (frac_y < 0.2 && game->map.grid[y - 1][x] == '1')
		game->player.y = floor(game->player.y) + 0.2;
	if (frac_y > 0.8 && game->map.grid[y + 1][x] == '1')
		game->player.y = floor(game->player.y) + 0.8;
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_plane_x;
	double	old_plane_y;

	old_dir_x = game->player.dir_x;
	old_dir_y = game->player.dir_y;
	old_plane_x = game->player.plane_x;
	old_plane_y = game->player.plane_y;
	game->player.dir_x = old_dir_x * cos(angle)
		- old_dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ old_dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle)
		- old_plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ old_plane_y * cos(angle);
}

void	handle_movement(t_game *game)
{
	if (game->keys[0])
		move_forward(game, 1.0);
	if (game->keys[1])
		move_strafe(game, -1.0);
	if (game->keys[2])
		move_forward(game, -1.0);
	if (game->keys[3])
		move_strafe(game, 1.0);
	if (game->keys[4])
		rotate_player(game, -game->player.rot_speed);
	if (game->keys[5])
		rotate_player(game, game->player.rot_speed);
	push_back(game);
}
