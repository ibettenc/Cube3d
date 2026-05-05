/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:11:21 by ibettenc          #+#    #+#             */
/*   Updated: 2026/05/05 18:50:04 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void    init_test_map(t_game *game) // /!\ map harcode, c juste en attendant le parsing
{
    static char *grid[] = {
        "111111111",
        "100000001",
        "101000101",
        "100000001",
        "111N00111",
        "100000001",
        "101000101",
        "100000001",
        "111111111",
        NULL
    };
    game->map.grid = grid;
    game->map.width = 9;
    game->map.height = 9;
}

int	game_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->screen.img_ptr, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_game  game;

    (void)argc;
    (void)argv;
    ft_memset(&game, 0, sizeof(t_game));
    init_test_map(&game);   // map hardcodée pour l'instant
    init_player(&game);
    init_mlx(&game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}

/*
J'en suis au point 3.2 : algo DDA

je dois faire la fonction perform_data, draw_column dans raycasting.c

*/