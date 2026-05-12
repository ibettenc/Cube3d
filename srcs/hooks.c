/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:16:27 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/09 17:17:02 by ivan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_all(t_game *game)
{
	// free screen
	if (game->screen.img_ptr)
		mlx_destroy_image(game->mlx, game->screen.img_ptr);

	// free window
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	if (game->mlx)
		mlx_destroy_display(game->mlx);

	// mlx ptr
	if (game->mlx)
		free(game->mlx);
}

int	close_window(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == 65307) // ESC sous Linux
		close_window(game);
	if (key == 119)
		game->keys[0] = 1;
	if (key == 97)
		game->keys[1] = 1;
	if (key == 115)
		game->keys[2] = 1;
	if (key == 100)
		game->keys[3] = 1;
	if (key == 65361)
		game->keys[4] = 1;
	if (key == 65363)
		game->keys[5] = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->keys[0] = 0;
	if (key == 97)
		game->keys[1] = 0;
	if (key == 115)
		game->keys[2] = 0;
	if (key == 100)
		game->keys[3] = 0;
	if (key == 65361)
		game->keys[4] = 0;
	if (key == 65363)
		game->keys[5] = 0;
	return (0);
}