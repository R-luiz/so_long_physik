/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:02:40 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void physic(t_game *game) {
    // Update speed based on acceleration
    game->player->speed.x += game->player->accel.x;
    game->player->speed.y += game->player->accel.y;

    // Check collisions with walls
    check_collisions_walls(game);

    // Speed limits
    game->player->speed.x = fmin(fmax(game->player->speed.x, -300), 300);
    game->player->speed.y = fmin(fmax(game->player->speed.y, -300), 300);

    // Update player position
    game->player->pos.x += game->player->speed.x;
    game->player->pos.y += game->player->speed.y;

    // Boundary checks
    game->player->pos.x = fmin(fmax(game->player->pos.x, 0), game->map_width * 50 - 30);
    game->player->pos.y = fmin(fmax(game->player->pos.y, 0), game->map_height * 50 - 30);
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
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
