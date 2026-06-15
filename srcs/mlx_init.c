/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:05:14 by ibettenc          #+#    #+#             */
/*   Updated: 2026/06/13 16:33:26 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		exit(EXIT_FAILURE);
	load_textures(game);
	get_data_addr(game);
	game->screen.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->screen.addr = mlx_get_data_addr(
			game->screen.img_ptr,
			&game->screen.bpp,
			&game->screen.line_len,
			&game->screen.endian
			);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
}
