/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:17:34 by ibettenc          #+#    #+#             */
/*   Updated: 2026/06/09 18:17:46 by ivan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void load_textures(t_game *game)
{
    game->textures[0].img_ptr = mlx_xpm_file_to_image(game->mlx,
        "srcs/textures/BRICK_BRIGHT.xpm", &game->textures[0].width, &game->textures[0].height);
    game->textures[1].img_ptr = mlx_xpm_file_to_image(game->mlx,
        "srcs/textures/BRICK_DARK.xpm", &game->textures[1].width, &game->textures[1].height);
    game->textures[2].img_ptr = mlx_xpm_file_to_image(game->mlx,
        "srcs/textures/BRICK_BRIGHT.xpm", &game->textures[2].width, &game->textures[2].height);
    game->textures[3].img_ptr = mlx_xpm_file_to_image(game->mlx,
        "srcs/textures/BRICK_DARK.xpm", &game->textures[3].width, &game->textures[3].height);
}

void get_data_addr(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        game->textures[i].addr = mlx_get_data_addr(
            game->textures[i].img_ptr, 
            &game->textures[i].bpp,
            &game->textures[i].line_len,
            &game->textures[i].endian);
        i++;
    }
}


int get_tex_id(t_ray * ray)
{
    int tex_id;
    
    if (ray->side == 0 && ray->step_x > 0)
        tex_id = 2; // EA (Est)
    if (ray->side == 0 && ray->step_x < 0)
        tex_id = 0; // NO (Nord)
    if (ray->side == 1 && ray->step_y > 0)
        tex_id = 1; // SO (Sud)
    if (ray->side == 1 && ray->step_y < 0)
        tex_id = 3; // WE (Ouest)    
    return (tex_id);
}

int get_tex_x(t_game *game, t_ray *ray, int tex_id)
{
    double ray_impact;
    
    if (ray->side == 0)
        ray_impact = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray_impact = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
    ray_impact = ray_impact - floor(ray_impact);
    return ((int)(ray_impact * game->textures[tex_id].width));
}
void draw_textured_wall(t_game *game, t_ray *ray, int x, int tex_id, int tex_x)
{
    double  step_tex;
    double  tex_pos;
    int     tex_y;
    int     color;
    char    *tex_addr;
    int     y;

    // Combien de pixels texture par pixel écran
    step_tex = (double)game->textures[tex_id].height / ray->line_height;
    
    // Position de départ dans la texture (gère le cas où le mur dépasse l'écran)
    tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step_tex;
    
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        tex_y = (int)tex_pos & (game->textures[tex_id].height - 1); // reste dans la texture
        tex_pos += step_tex;

        // Adresse du pixel dans le buffer de la texture
        tex_addr = game->textures[tex_id].addr
            + (tex_y * game->textures[tex_id].line_len
            + tex_x * (game->textures[tex_id].bpp / 8));
        color = *(unsigned int *)tex_addr;

        // Assombrir les murs côté Y
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;

        put_pixel(&game->screen, x, y, color);
        y++;
    }
}
