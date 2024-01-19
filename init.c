/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:17:07 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 18:43:10 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	init_imgs(t_game *game)
{
	int	width;
	int	height;

	game->player_img = mlx_xpm_file_to_image(game->mlx, "./imgs/player2.xpm",
		&width, &height);
    game->playerm_img = mlx_xpm_file_to_image(game->mlx, "./imgs/playerm.xpm",
		&width, &height);
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm",
        &width, &height);
    game->enemy_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemy.xpm",
        &width, &height);
    game->enemym_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemym.xpm",
        &width, &height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "./imgs/exit.xpm",
        &width, &height);
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "./imgs/collect.xpm",
        &width, &height);
    game->background_img = mlx_xpm_file_to_image(game->mlx, "./imgs/void.xpm",
        &width, &height);
}

t_point find_player(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'P')
            {
                game->map[i][j] = '0';
                return ((t_point){j * 50, i * 50});
            }
            j++;
        }
        i++;
    }
    return ((t_point){0, 0});
}

void    init_entities(t_game *game)
{
    game->player = (t_player *)arena_alloc(game->arena, sizeof(t_player));
    game->player->ent_type = PLAYER;
    game->player->pos = find_player(game);
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

t_game	*game_init(int argc, char **argv)
{
	t_arena	*arena;
	t_game	*game;

	arena = arena_init(1000000);
	game = (t_game *)arena_alloc(arena, sizeof(t_game));
	if (!game)
		return (NULL);
	game->arena = arena;
	game->mlx = mlx_init();
    game->nb_map = 2;
	create_file_name(game, argc, argv);
	parse_map(game);
	game->win = mlx_new_window(game->mlx, game->map_width * 50, game->map_height * 50, "so_long_gravity");
    game->gravity = (t_accel *)arena_alloc(game->arena, sizeof(t_accel));
    game->gravity->x = 0;
    game->gravity->y = 0;
    gettimeofday(&game->last_frame, NULL);
    game->time = get_time(game);
	// check_map(game);
    init_imgs(game);
    init_entities(game);
	return (game);
}
