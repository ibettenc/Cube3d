/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:55:44 by ivan              #+#    #+#             */
/*   Updated: 2026/06/06 20:10:36 by ivan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void    move_forward(t_game *game, double dir)
{
    double new_x;
    double new_y;

    new_x = game->player.x + game->player.dir_x * game->player.move_speed * dir;
    new_y = game->player.y + game->player.dir_y * game->player.move_speed * dir;
    if (game->map.grid[(int)game->player.y][(int)(new_x + WALL_OFFSET * game->player.dir_x)] != '1') // (cast int car new_x et player.y sont des double)
        game->player.x = new_x;
    if (game->map.grid[(int)new_y][(int)(game->player.x  + WALL_OFFSET * game->player.dir_y)] != '1') // (cast int car new_y et player.x sont des double)
        game->player.y = new_y;
}

static void    move_strafe(t_game *game, double dir)
{
    double new_x;
    double new_y;

    new_x = game->player.x + (-game->player.dir_y) * game->player.move_speed * dir; // tout est la mm chose sauf (-game->player.dir_y)
    new_y = game->player.y + game->player.dir_x * game->player.move_speed * dir;
    if (game->map.grid[(int)game->player.y][(int)(new_x + WALL_OFFSET * (-game->player.dir_y))] != '1')
        game->player.x = new_x;
    if (game->map.grid[(int)new_y][(int)(game->player.x + WALL_OFFSET * (-game->player.dir_y))] != '1')
        game->player.y = new_y;
}

static void rotate_player(t_game *game, double angle)
{
    double old_dir_x;
    double old_dir_y;
    double old_plane_x;
    double old_plane_y;

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

void    handle_movement(t_game *game)
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
}
