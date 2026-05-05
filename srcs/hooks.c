/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:16:27 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/04 18:43:59 by ibettenc         ###   ########.fr       */
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
	return (0);
}