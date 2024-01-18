/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:17:07 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 18:02:27 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	init_imgs(t_game *game)
{
	int	width;
	int	height;

	game->player_img = mlx_xpm_file_to_image(game->mlx, "./imgs/player2.xpm",
		&width, &height);
    // game->playerm_img = mlx_xpm_file_to_image(game->mlx, "./imgs/playerm.xpm",
		// &width, &height);
    // game->wall_img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm",
        // &width, &height);
    // game->enemy_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemy.xpm",
    //     &width, &height);
    // game->enemym_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemym.xpm",
    //     &width, &height);
    // game->exit_img = mlx_xpm_file_to_image(game->mlx, "./imgs/exit.xpm",
        // &width, &height);
    // game->collectible_img = mlx_xpm_file_to_image(game->mlx, "./imgs/collect.xpm",
        // &width, &height);
    game->background_img = mlx_xpm_file_to_image(game->mlx, "./imgs/background2.xpm",
        &width, &height);
}

void    init_entities(t_game *game)
{
    game->player = (t_player *)arena_alloc(game->arena, sizeof(t_player));
    game->player->ent_type = PLAYER;
    game->player->pos.x = 450;
    game->player->pos.y = 450;
    game->player->speed.x = 0;
    game->player->speed.y = 0;
    game->player->accel.x = 0;
    game->player->accel.y = 0;
    game->player->mass = 1;
}

float   get_time(t_game *game)
{
    struct timeval  current_time;
    float           time;

    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec - game->last_frame.tv_sec) * 1000.0;
    time += (current_time.tv_usec - game->last_frame.tv_usec) / 1000.0;
    return (time);
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
	game->win = mlx_new_window(game->mlx, 1000, 1000, "so_long_gravity");
    game->gravity = (t_accel *)arena_alloc(game->arena, sizeof(t_accel));
    game->gravity->x = 0;
    game->gravity->y = 1;
    gettimeofday(&game->last_frame, NULL);
    game->time = get_time(game);
    init_imgs(game);
    init_entities(game);
	return (game);
}
