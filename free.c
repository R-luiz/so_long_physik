/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:48:08 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 17:00:58 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void    free_imgs(t_game *game)
{
    mlx_destroy_image(game->mlx, game->player_img);
    mlx_destroy_image(game->mlx, game->playerm_img);
    mlx_destroy_image(game->mlx, game->wall_img);
    // mlx_destroy_image(game->mlx, game->enemy_img);
    // mlx_destroy_image(game->mlx, game->enemym_img);
    mlx_destroy_image(game->mlx, game->exit_img);
    mlx_destroy_image(game->mlx, game->collectible_img);
    mlx_destroy_image(game->mlx, game->background_img);
}

int    safeexit(void *data)
{
    t_game    *game;

    game = (t_game *)data;
    free_imgs(game);
    mlx_clear_window(game->mlx, game->win);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    arena_destroy(game->arena);
    exit(0);
    return (0);
}
