/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 15:42:03 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	//limit at 1 refresh per 0.5 seconds
	if (get_time(game) > 1.8)
	{
		gettimeofday(&game->last_frame, NULL);
		//gravity
		physic(game);
		if (game->player->speed.x != 0 || game->player->speed.y != 0)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->background_img, 0, 0);
			mlx_do_sync(game->mlx);
			mlx_put_image_to_window(game->mlx, game->win, game->player_img,
				game->player->pos.x, game->player->pos.y);
			mlx_do_sync(game->mlx);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = game_init();
	
	if (!game)
		return (1);
	game->nb_map = 2;
	create_file_name(game, argc, argv);
	parse_map(game);
	check_map(game);
	mlx_hook(game->mlx, 33, 1L << 17, safeexit, (void *)game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, (void *)game);
	// mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_press2, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
