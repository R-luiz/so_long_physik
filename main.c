/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 19:38:18 by rluiz            ###   ########.fr       */
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
		game->player->accel.y *= 0.9;
		game->player->accel.x *= 0.9;
		game->player->accel.y += game->gravity->y;
		game->player->accel.x += game->gravity->x;
		game->player->speed.y += game->player->accel.y;
		game->player->speed.x += game->player->accel.x;
		if (game->player->accel.y > 50)
			game->player->accel.y = 50;
		if (game->player->accel.x > 50)
			game->player->accel.x = 50;
		if (game->player->accel.y < -50)
			game->player->accel.y = -50;
		if (game->player->accel.x < -50)
			game->player->accel.x = -50;
		if (game->player->pos.x < 0)
		{
			game->player->pos.x = 0;
			game->player->speed.x *= -0.9;
			game->player->accel.x *= -1;
		}
		if (game->player->pos.y < 0)
		{
			game->player->pos.y = 0;
			game->player->speed.y *= -0.9;
			game->player->accel.y *= -1;
		}
		if (game->player->pos.x > 950)
		{
			game->player->pos.x = 950;
			game->player->speed.x *= -0.9;
			game->player->accel.x *= -1;
		}
		if (game->player->pos.y > 950)
		{
			game->player->pos.y = 950;
			game->player->speed.y *= -0.5;
			game->player->accel.y *= -0.5;
		}
		if (game->player->speed.x > 700)
			game->player->speed.x = 700;
		if (game->player->speed.y > 700)
			game->player->speed.y = 700;
		if (game->player->speed.x < -700)
			game->player->speed.x = -700;
		if (game->player->speed.y < -700)
			game->player->speed.y = -700;
		if (game->player->pos.y >= 940)
		{
			game->player->speed.x += game->player->speed.x * -0.01;
		}
		game->player->pos.x += game->player->speed.x / 100;
		game->player->pos.y += game->player->speed.y / 100;
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

int	main(void)
{
	t_game	*game;

	game = game_init();
	if (!game)
		return (1);
	mlx_hook(game->mlx, 33, 1L << 17, safeexit, (void *)game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, (void *)game);
	// mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_press2, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
