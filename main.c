/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 16:47:30 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"
void	physic(t_game *game)
{
	game->player->accel.y *= 0.9;
	game->player->accel.x *= 0.9;
	game->player->accel.y += game->gravity->y;
	game->player->accel.x += game->gravity->x;
	game->player->speed.y += game->player->accel.y;
	game->player->speed.x += game->player->accel.x;
	check_collisions_walls(game);
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
}

void	refresh_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx_clear_window(game->mlx, game->win);
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, j * 50, i * 50);
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, j * 50, i * 50);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit_img, j * 50, i * 50);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * 50, i * 50);
			else if (game->map[i][j] == 'X')
				mlx_put_image_to_window(game->mlx, game->win, game->enemy_img, j * 50, i * 50);
			else if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * 50, i * 50);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player->pos.x, game->player->pos.y);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (get_time(game) > 2)
	{
		gettimeofday(&game->last_frame, NULL);
		//gravity
		physic(game);
		if (game->player->speed.x != 0 || game->player->speed.y != 0)
		{
			refresh_window(game);
			mlx_do_sync(game->mlx);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = game_init(argc, argv);
	if (!game)
		return (1);

	mlx_hook(game->mlx, 33, 1L << 17, safeexit, (void *)game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, (void *)game);
	// mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_press2, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
