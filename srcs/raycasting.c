/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:17:36 by ibettenc          #+#    #+#             */
/*   Updated: 2026/06/09 17:39:22 by ivan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WIN_WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
}

void	init_dda(t_game *game, t_ray *ray)
{
	ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_x); // cest quoi ca deja 
	ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_y);
	if (ray->ray_dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
}

// avance jusqu'au mur
void    perform_dda(t_game *game, t_ray *ray)
{
    while (game->map.grid[ray->map_y][ray->map_x] != '1')
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // le ray touche mur cote N ou S
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // le ray touche mur cote O ou E
        }
    }
}

void calcul_column(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = WIN_HEIGHT / ray->perp_wall_dist;
	ray->draw_start = WIN_HEIGHT / 2 - ray->line_height / 2;
	ray->draw_end = WIN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void    draw_column(t_game *game, t_ray *ray, int x)
{
    int     tex_id;
    int     tex_x;
    int     y;

    calcul_column(ray);
    tex_id = get_tex_id(ray);
    tex_x = get_tex_x(game, ray, tex_id);

    // Plafond
    y = 0;
    while (y < ray->draw_start)
    {
        put_pixel(&game->screen, x, y, game->ceil_color);
        y++;
    }

    // Mur texturé
    draw_textured_wall(game, ray, x, tex_id, tex_x);

    // Sol
    y = ray->draw_end + 1;
    while (y < WIN_HEIGHT)
    {
        put_pixel(&game->screen, x, y, game->floor_color);
        y++;
    }
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		init_dda(game, &ray);
		perform_dda(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}
