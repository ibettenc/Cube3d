/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:32:36 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/05 18:24:44 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"

# define WIN_WIDTH   1280
# define WIN_HEIGHT  720

typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_player {
    double  x;         // position dans la map (en cases)
    double  y;
    double  dir_x;     // direction
    double  dir_y;
    double  plane_x;   // FOV
    double  plane_y;
    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_map {
    char    **grid;    // grille 2D
    int     width;
    int     height;
}   t_map;

typedef struct s_ray
{
    int     map_x;      // case actuelle dans la map
    int     map_y;
    int     step_x;
    int     step_y;
    int     side;
    int     line_height;
    int     draw_end;
    int     draw_start;
    double  ray_dir_x;  // direction du rayon
    double  ray_dir_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    double  perp_wall_dist;
}   t_ray;

typedef struct s_game {
    void        *mlx;
    void        *win;
    t_img       screen;      // image buffer principale
    t_img       textures[4]; // 0=NO, 1=SO, 2=EA, 3=WE
    t_player    player;
    t_map       map;
    int         floor_color;
    int         ceil_color;
}   t_game;

/* mlx_init.c */
void	init_mlx(t_game *game);

/* hooks.c */
int		key_press(int key, t_game *game);
int		close_window(t_game *game);
int		game_loop(t_game *game);

/* render.c */
void	put_pixel(t_img *img, int x, int y, int color);

/* player.c */
void	init_player(t_game *game);

/* raycasting.c */
void    init_ray(t_game *game, t_ray *ray, int x);
void    init_dda(t_game *game, t_ray *ray);
void    perform_dda(t_game *game, t_ray *ray);
void    draw_column(t_game *game, t_ray *ray, int x);
void    raycast(t_game *game);

#endif