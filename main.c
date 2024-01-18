/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 17:05:13 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	*game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_put_image_to_window(game->mlx, game->win, game->background_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->player_img,
		game->player->pos.x, game->player->pos.y);
	return (0);
}

int	main(void)
{
	t_game	*game;

	game = game_init();
	if (!game)
		return (1);
	mlx_hook(game->mlx, 33, 1L << 17, safeexit, (void *)game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
