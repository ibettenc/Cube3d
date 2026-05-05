/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:17:36 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/05 18:48:39 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	raycast(t_game *game)
{
	int	x;
	// 1. calculer camera_x et ray_dir
	x = 0;
	while (x < WIN_WIDTH)
	{

		// 2. DDA


		
		// 3. calculer line_height, draw_start, draw_end
		// 4. dessiner la colonne
		x++;
	}
}

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
	ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_x);
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
void	perform_dda(t_game *game, t_ray *ray); 

// calcule line_height, draw_start, draw_end, dessine
void	draw_column(t_game *game, t_ray *ray, int x);

void	raycasting(t_game *game);
