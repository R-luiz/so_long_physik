/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:17:07 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 16:20:42 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	init_imgs(t_game *game)
{
	int	width;
	int	height;

	game->player_img = mlx_xpm_file_to_image(game->mlx, "./imgs/player.xpm",
		&width, &height);
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm",
        &width, &height);
    game->enemy_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemy.xpm",
        &width, &height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "./imgs/exit.xpm",
        &width, &height);
}

t_game	*game_init(void)
{
	t_arena	*arena;
	t_game	*game;

	arena = arena_init(1000000);
	game = (t_game *)arena_alloc(arena, sizeof(t_game));
	if (!game)
		return (NULL);
	game->arena = arena;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 860, 540, "so_long_gravity");
	return (game);
}
